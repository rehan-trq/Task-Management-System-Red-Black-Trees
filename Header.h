#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int RED = 0;
const int BLACK = 1;

template <typename T>
struct Node {
    T data;
    int color;
    Node* parent;
    Node* left;
    Node* right;

    Node(T val) : data(val), color(RED), parent(nullptr), left(nullptr), right(nullptr) {}
};

template <typename T>
class RedBlackTree {
private:
    Node<T>* root;

    // Helper functions
    void leftRotate(Node<T>* x);
    void rightRotate(Node<T>* x);
    void insertFixup(Node<T>* z);
    void transplant(Node<T>* u, Node<T>* v);
    void deleteFixup(Node<T>* x);

public:
    RedBlackTree() : root(nullptr) {}

    // Public functions
    void insert(T key);
    void remove(T key);
    void printTree(Node<T>* node, int indent = 0);
    void inorderTraversal(Node<T>* node);
    Node<T>* getRoot() const { return root; }
};

template <typename T>
void RedBlackTree<T>::leftRotate(Node<T>* x) {
    Node<T>* y = x->right;
    x->right = y->left;

    if (y->left != nullptr)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

template <typename T>
void RedBlackTree<T>::rightRotate(Node<T>* y) {
    Node<T>* x = y->left;
    y->left = x->right;

    if (x->right != nullptr)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == nullptr)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

template <typename T>
void RedBlackTree<T>::insertFixup(Node<T>* z) {
    while (z != root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node<T>* y = z->parent->parent->right;
            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        }
        else {
            Node<T>* y = z->parent->parent->left;
            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

template <typename T>
void RedBlackTree<T>::insert(T key)
{
    Node<T>* z = new Node<T>(key);
    Node<T>* y = nullptr;
    Node<T>* x = root;

    while (x != nullptr) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == nullptr)
        root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    insertFixup(z);
}

template <typename T>
void RedBlackTree<T>::transplant(Node<T>* u, Node<T>* v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != nullptr)
        v->parent = u->parent;
}

template <typename T>
void RedBlackTree<T>::deleteFixup(Node<T>* x) {
    while (x != root && (x == nullptr || x->color == BLACK)) {
        if (x == x->parent->left) {
            Node<T>* w = x->parent->right;
            if (w != nullptr && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if ((w->left == nullptr || w->left->color == BLACK) &&
                (w->right == nullptr || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right == nullptr || w->right->color == BLACK) {
                    if (w->left != nullptr)
                        w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right != nullptr)
                    w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        }
        else {
            Node<T>* w = x->parent->left;
            if (w != nullptr && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if ((w->right == nullptr || w->right->color == BLACK) &&
                (w->left == nullptr || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left == nullptr || w->left->color == BLACK) {
                    if (w->right != nullptr)
                        w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left != nullptr)
                    w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    if (x != nullptr)
        x->color = BLACK;
}

template <typename T>
void RedBlackTree<T>::remove(T key) {
    Node<T>* z = root;
    while (z != nullptr) {
        if (key == z->data) {
            Node<T>* y = z;
            Node<T>* x;
            int yOriginalColor = y->color;
            if (z->left == nullptr) {
                x = z->right;
                transplant(z, z->right);
            }
            else if (z->right == nullptr) {
                x = z->left;
                transplant(z, z->left);
            }
            else {
                y = z->right;
                while (y->left != nullptr)
                    y = y->left;
                yOriginalColor = y->color;
                x = y->right;
                if (y->parent == z)
                    x->parent = y;
                else {
                    transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
            if (yOriginalColor == BLACK)
                deleteFixup(x);
            delete z;
            break;
        }
        else if (key < z->data) {
            z = z->left;
        }
        else {
            z = z->right;
        }
    }
}

template <typename T>
void RedBlackTree<T>::printTree(Node<T>* node, int indent) {
    if (node != nullptr) {
        if (node->left != nullptr)
            printTree(node->left, indent + 4);
        if (indent > 0)
            cout << std::setw(indent) << " ";
        cout << node->data << " (" << (node->color == RED ? "RED" : "BLACK") << ")" << endl;
        if (node->right != nullptr)
            printTree(node->right, indent + 4);
    }
}

template <typename T>
void RedBlackTree<T>::inorderTraversal(Node<T>* node) {
    if (node != nullptr) {
        inorderTraversal(node->left);
        cout << node->data << " ";
        inorderTraversal(node->right);
    }
}


class AssigneeNode
{
public:

    string firstname;
    string lastname;
    string address;
    string dob;
    string assigneeid;
    AssigneeNode* left;
    AssigneeNode* right;
    AssigneeNode* parent;
    string color;

    AssigneeNode()
    {
        firstname = " ";
        lastname = " ";
        address = " ";
        dob = " ";
        assigneeid = " ";
        left = right = parent = nullptr;
        color = "Red";
    }

};

class AssigneeTree
{
public:

    AssigneeNode* root;
    RedBlackTree<string> rb;

    AssigneeTree()
    {
        root = nullptr;
    }

    AssigneeNode* rightrotation(AssigneeNode* root)
    {
        AssigneeNode* temp = root->left;
        root->left = temp->right;
        temp->right = root;

        //root->height = max(height(root->left), height(root->right)) + 1;
        //temp->height = max(height(temp->left), height(temp->right)) + 1;
        return temp;
    }

    AssigneeNode* leftrotation(AssigneeNode* root)
    {
        AssigneeNode* temp = root->right;
        root->right = temp->left;
        temp->left = root;

        //root->height = max(height(root->left), height(root->right)) + 1;
        //temp->height = max(height(temp->left), height(temp->right)) + 1;
        return temp;
    }

    void add(AssigneeNode* node)
    {
        AssigneeNode* curr = new AssigneeNode;
        curr->firstname = node->firstname;
        curr->lastname = node->lastname;
        curr->address = node->address;
        curr->dob = node->dob;
        rb.insert(node->assigneeid);
    }

    stringstream& displayid(stringstream& actualOutput, const string& id, AssigneeNode* node)
    {
        if (node != nullptr)
        {
            if (id == node->assigneeid)
            {
                actualOutput << "Name: " << node->firstname << " " << node->lastname << " ";
                actualOutput << "Address: " << node->address << " ";
                actualOutput << "DOB: " << node->dob << " ";
                actualOutput << "AssigneeID: " << node->assigneeid << "\n";
                return actualOutput;
            }

            else if (id > node->assigneeid)
            {
                displayid(actualOutput, id, node->right);
            }

            else
            {
                displayid(actualOutput, id, node->left);
            }
        }
        return actualOutput;
    }



};

class taskManagementSystem
{
public:

    AssigneeTree atree;
    int id_counter = 0;
    const string AssigneeIDPrefix = "A";

    void addAssignee(string fn, string ln, string add, string db)
    {
        AssigneeNode* newnode = new AssigneeNode;
        newnode->firstname = fn;
        newnode->lastname = ln;
        newnode->address = add;
        newnode->dob = db;

        ostringstream assigneeIDStream;
        assigneeIDStream << AssigneeIDPrefix << std::setw(3) << std::setfill('0') << id_counter;
        newnode->assigneeid = assigneeIDStream.str();

        // Increment the counter for the next assignee
        id_counter++;
        atree.add(newnode);

    }

    void displaybyID(stringstream& actualOutput, string id)
    {

        /*if (atree.root != nullptr)
        {
            atree.displayid(actualOutput, id, atree.root);
        }*/
        atree.displayid(actualOutput, id, atree.root);
    }
};