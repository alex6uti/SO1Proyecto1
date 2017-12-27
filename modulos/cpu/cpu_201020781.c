#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/vmstat.h>
#include <linux/swap.h>
#include <linux/module.h>
#include <linux/sched.h>

static const char * const task_state_array[] = {
		"running", "sleep",	"D",	"stoped",	"t",	"X",	"zombie",
};

static inline const char *get_task_state(struct task_struct *tsk)
{
	unsigned int state = (tsk->state | tsk->exit_state) & TASK_REPORT;
	return task_state_array[fls(state)];
}

static int adminprocinfo_proc_show(struct seq_file *m, void *v)
{
	struct task_struct *task;

	seq_printf(m,"201020781\n" 
				 "Mario Alexander Gutierrez Hernandez\n"
				 "OpenSuse  - CPU\n\n"); 

	for_each_process(task){
		seq_printf(m, "PID: %d   Nombre: %s   Estado: %s\n", task->pid, task->comm, get_task_state(task));
	}

    	return 0;
	#undef K
}






static int adminprocinfo_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, adminprocinfo_proc_show, NULL);
}

static const struct file_operations adminprocinfo_proc_fops = {
    .owner      = THIS_MODULE,
    .open       = adminprocinfo_proc_open,
    .read       = seq_read,
    .llseek     = seq_lseek,
    .release    = single_release,
};

static int __init proc_adminprocinfo_init(void)
{
	printk(KERN_INFO "Mario Alexander Gutierrez Hernandez\n");
    proc_create("cpu_201020781", 0, NULL, &adminprocinfo_proc_fops);
    return 0;
}

static void __exit proc_adminprocinfo_exit(void)
{
	printk(KERN_INFO "SistemasOperativos1\n");
    remove_proc_entry("cpu_201020781", NULL);
}

module_init(proc_adminprocinfo_init);
module_exit(proc_adminprocinfo_exit);

MODULE_AUTHOR("Mario Alexander Gutierrez Hernandez - 201020781");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A cpu_201020781 /proc file.");
