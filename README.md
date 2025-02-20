# Task Management System

## Overview

The **Task Management System** is a structured solution designed to efficiently manage tasks, priorities, and assignees. Utilizing **Red-Black Trees**, the system ensures optimal performance in task assignment, prioritization, and tracking. Organizations and teams can use this system to allocate tasks, monitor progress, and streamline workflows.

## Features

- **Task Assignment:** Allocate tasks to assignees with priority levels.
- **Priority-Based Task Management:** Organize tasks efficiently based on their priority.
- **Assignee Management:** Add, remove, and list assignees, including those without tasks.
- **Task Reassignment:** Transfer tasks between different assignees.
- **Completion Tracking:** Mark tasks as completed and maintain a record of them.
- **Priority-Based Search:** Retrieve tasks within a specific priority range.
- **Task Deletion:** Remove tasks and dynamically update priorities.

## Data Structures Used

### Red-Black Trees (RB Trees):
   - Self-balancing binary search trees for efficient task and assignee management.
   - Provides fast insertion, deletion, and lookup operations.

### Priority Queue:
   - Custom priority queue to manage tasks dynamically based on their priority.
   - Ensures high-priority tasks are processed first.

## Core Functionalities

### 1. Adding an Assignee:
   - Registers a new assignee with a unique ID.
   - **Syntax:**
     ```cpp
     addAssignee(firstName, lastName, address, dateOfBirth);
     ```

### 2. Creating a Task:
   - Defines a task with a task ID, description, priority level, and assigned individual.
   - **Syntax:**
     ```cpp
     addTask(taskID, description, priorityLevel, assigneeID);
     ```

### 3. Retrieve Assignee Information:
   - Fetch details of an assignee using either their ID or name.
   - **Syntax:**
     ```cpp
     displaybyID(outputStream, assigneeID);
     displaybyname(outputStream, firstName, lastName);
     ```

### 4. Identifying Assignees Without Tasks:
   - Lists all assignees who do not have any tasks assigned.
   - **Syntax:**
     ```cpp
     AssigneeWithNoTask(outputStream);
     ```

### 5. Reassigning Tasks:
   - Transfers all tasks from one assignee to another.
   - **Syntax:**
     ```cpp
     ShiftTask(assigneeID1, assigneeID2);
     ```

### 6. Displaying Task Queue:
   - Displays tasks sorted by priority along with their assignees.
   - **Syntax:**
     ```cpp
     printTaskQueue(outputStream);
     ```

### 7. Marking a Task as Completed:
   - Updates the status of a task to completed.
   - **Syntax:**
     ```cpp
     completeTask(taskID);
     ```

### 8. Modifying Task Priority:
   - Adjusts the priority level of an existing task.
   - **Syntax:**
     ```cpp
     updateTaskPriority(taskID, newPriorityLevel);
     ```

### 9. Finding the Highest Priority Task:
   - Retrieves and displays the task with the highest priority.
   - **Syntax:**
     ```cpp
     findHighestPriorityTask(outputStream);
     ```

### 10. Removing a Task:
   - Deletes a task from the system when no longer needed.
   - **Syntax:**
     ```cpp
     deleteTask(taskID);
     ```

### 11. Counting Total Tasks:
   - Displays the total number of tasks in the system.
   - **Syntax:**
     ```cpp
     countTotalTasks(outputStream);
     ```

### 12. Searching Tasks by Priority Range:
   - Finds and lists tasks within a specified priority range.
   - **Syntax:**
     ```cpp
     searchTasksByPriorityRange(priorityLow, priorityHigh, outputStream);
     ```

### 13. Viewing Completed Tasks:
   - Displays all tasks that have been marked as completed.
   - **Syntax:**
     ```cpp
     displayCompletedTasks(outputStream);
     ```

## License

This project is released under the **MIT License**, allowing for open-source contribution, usage, and modification. Contributions are welcome!
