#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched/signal.h>
#include <linux/mm.h>

#define PROC_NAME "mem_tree"

static void show_process_tree(struct seq_file *m, struct task_struct *task, int depth) {
    struct mm_struct *mm = task->mm;
    seq_printf(m, "%*s|- PID: %d | Parent: %d | Comm: %s\n",
               depth * 4, "", task->pid, task->parent->pid, task->comm);

    if (mm) {
        seq_printf(m, "%*s   Text:  0x%lx\n", depth * 4, "", mm->start_code);
        seq_printf(m, "%*s   Data:  0x%lx\n", depth * 4, "", mm->start_data);
        seq_printf(m, "%*s   Heap:  0x%lx\n", depth * 4, "", mm->start_brk);
        seq_printf(m, "%*s   Stack: 0x%lx\n", depth * 4, "", mm->start_stack);
    }

    struct task_struct *child;
    struct list_head *list;
    list_for_each(list, &task->children) {
        child = list_entry(list, struct task_struct, sibling);
        show_process_tree(m, child, depth + 1);
    }
}

static int show_mem_map(struct seq_file *m, void *v) {
    struct task_struct *task;
    seq_printf(m, "Process Tree with Memory Regions:\n");
    for_each_process(task) {
        if (task->pid == 1) { // Start from init/systemd
            show_process_tree(m, task, 0);
            break;
        }
    }
    return 0;
}

static int mem_map_open(struct inode *inode, struct file *file) {
    return single_open(file, show_mem_map, NULL);
}

static const struct proc_ops proc_ops = {
    .proc_open = mem_map_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init mem_map_init(void) {
    proc_create(PROC_NAME, 0, NULL, &proc_ops);
    printk(KERN_INFO "Kernel Module Loaded: /proc/%s\n", PROC_NAME);
    return 0;
}

static void __exit mem_map_exit(void) {
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "Kernel Module Unloaded\n");
}

module_init(mem_map_init);
module_exit(mem_map_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sumeet Tummaramatti");
MODULE_DESCRIPTION("Linux Kernel Module for Process Tree with Memory Regions");

