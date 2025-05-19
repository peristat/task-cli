# task-cli

  
**Task CLI** is a simple and lightweight command-line application for tracking and managing your daily tasks. It uses a JSON file to persist task data locally.

---
 
## ✨ Features
- Add, update, and delete tasks
- Mark tasks as **To Do**, **In Progress**, or **Done**
- List all tasks or filter by status:
	- All tasks
	- Done tasks
	- To Do tasks
	- In Progress tasks

---

## 🛠 Installation 
### Requirements

- **C++11** or later
- [nlohmann/json](https://github.com/nlohmann/json) library (single-header version)
- GNU Make (optional but recommended)
 
### Steps

1. **Clone the repository**:
```bash
git clone https://github.com/peristat/task-cli.git
cd task-cli
```

2. **Ensure the JSON header is in place**:
- Make sure `include/json.hpp exists.
- if not, download it from:
	https://github.com/nlohmann/json/releases

3. **Build the project:**:
```bash
make
```
  Or manually using g++:
  ```bash
    g++ -std=c++11 -Iinclude -Wall -Wextra main.cpp -o task-cli
  ```

4.Run the CLI:
  ```bash
  ./task-cli
  ```
Or to run `task-cli` from anywhere from the terminal:
Move the binary to a directory in your PATH, such as `/usr/local/bin`:
```bash
sudo mv task-cli /usr/local/bin
```
And verify if works:
```bash
task-cli list
```

# 🚀 example usage

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

# 🧾Task Properties

Each task have the following properties:

- `Id`: A unique identifier for the task
- `Description`: A short description of the task
- `Status`: The status of the task (`todo`, `in-progress`, `done`)
- `CreatedAt`: The date and time when the task was created
- `UpdatedAt`: The date and time when the task was last updated

  Tasks are stored in a JSON file (`storage.json`) like this:
  ```json
  {
    "next_id": 12,
    "task": [
        {
            "CreateAt": "Mon May 19 23:37:41 2025\n",
            "Description": "Prepare for the maths test",
            "Id": 9,
            "Status": "In Progress",
            "UpdatedAt": "Mon May 19 23:38:19 2025\n"
        },
        {
            "CreateAt": "Mon May 19 23:39:45 2025\n",
            "Description": "SLEEP",
            "Id": 10,
            "Status": "To Do",
            "UpdatedAt": "Mon May 19 23:39:45 2025\n"
        },
        {
            "CreateAt": "Mon May 19 23:40:31 2025\n",
            "Description": "Go for a walk",
            "Id": 11,
            "Status": "Done",
            "UpdatedAt": "Mon May 19 23:40:52 2025\n"
        }
    ]
}

```
