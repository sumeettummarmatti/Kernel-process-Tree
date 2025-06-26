# 🧠 Memory-Aware Process Tree – Linux Kernel Module + User-space Process Spawner

This project implements a Linux kernel module and a user-space program that together demonstrate how to:

- Dynamically spawn child processes in user space
- Traverse the process tree from a specific parent process ID
- Display the memory usage (virtual memory) of each process in a tree format via `/proc/mem_tree`

---

## ⚙️ Requirements

- Linux system with kernel headers installed
- GCC compiler
- Root access (`sudo`)
- `bash` shell
- Kernel supports `/proc` and module loading (`insmod`, `rmmod`)

---

## 🔧 Build Instructions

### 1. Clone the repo or download files
```bash
git clone https://github.com/your-username/your-repo-name.git
cd your-repo-name
```
### 2. Make the run script executable
```bash
chmod +x run.sh
```
## 🚀 Running the Project

### To build everything, run the user program, and print the memory-aware process tree:

```bash
./run.sh
```

This will:
	1.	Build the kernel module and user binary
	2.	Run the user-space program (./user) which spawns child processes
	3.	Capture the parent PID and pass it to the kernel module
	4.	Insert the kernel module with that PID
	5.	Print the process tree with memory usage from /proc/mem_tree
	6.	Remove the kernel module
	7.	Clean up build artifacts


 ### 🧪 Sample Output

```bash
 Memory-Aware Process Tree from PID 14452:
|- PID: 14452 | Name: user | VM: 1268 KB
  |- PID: 14453 | Name: child1 | VM: 1024 KB
  |- PID: 14454 | Name: child2 | VM: 1040 KB
```
