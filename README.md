# task-cli
Task tracker is simple CLI application used to track and manage your tasks.
# features
- Add, Update, and Delete tasks
- Mark a task as in progress or done
- List all tasks
- List all tasks that are done 
- List all tasks that are not done 
- List all tasks that are in progress
# example
```bash
# Adding a new task
task-cli add Do maths assignment
# Output: Task added successfully (ID: 1)

#Updating and deleting tasks
task-cli update 1 Do maths assignment and cook dinner

# Marking a task as in progress or done
task-cli mark-inprogress 1
task-cli mark-done 1

# Listing all tasks
task-cli list

# Listing tasks by status
task-cli list done
task-cli list todo
task-cli list in-progress
```

# Task Properties
Each task have the following properties:

- `Id`: A unique identifier for the task
- `Description`: A short description of the task
- `Status`: The status of the task (`todo`, `in-progress`, `done`)
- `CreatedAt`: The date and time when the task was created
- `UpdatedAt`: The date and time when the task was last updated

This properties are stored in JSON file in following manner:
