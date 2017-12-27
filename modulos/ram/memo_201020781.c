#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/vmstat.h>
#include <linux/swap.h>
#include <linux/module.h>


static int memoinfo_proc_show(struct seq_file *m, void *v)
{
	struct sysinfo i;
	long ram_total;
	long ram_libre;
	long porcentaje_utilizado;

	#define K(x) ((x) << (PAGE_SHIFT - 10))

	si_meminfo(&i);

	ram_total = ((uint64_t) i.totalram * i.mem_unit)/1024;
	ram_libre = ((uint64_t) i.freeram * i.mem_unit)/1024;
	porcentaje_utilizado = ((ram_total - ram_libre)*100)/ram_total;


	seq_printf(m,"201020781\n" 
				 "Mario Alexander Gutierrez Hernandez\n"
				 "OpenSuse  - Info MemRAM\n\n" 
					"To: %8lu Kb\n" "Li: %8lu Kb\n" "Ut: %8lu %%\n", ram_total, ram_libre, porcentaje_utilizado);

    	return 0;
	#undef K
}


static int memoinfo_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, memoinfo_proc_show, NULL);
}

static const struct file_operations memoinfo_proc_fops = {
    .owner      = THIS_MODULE,
    .open       = memoinfo_proc_open,
    .read       = seq_read,
    .llseek     = seq_lseek,
    .release    = single_release,
};

static int __init proc_memoinfo_init(void)
{
	printk(KERN_INFO "201020781\n");
    proc_create("memo_201020781", 0, NULL, &memoinfo_proc_fops);
    return 0;
}

static void __exit proc_memoinfo_exit(void)
{
	printk(KERN_INFO "SistemasOperativos1\n");
    remove_proc_entry("memo_201020781", NULL);
}

module_init(proc_memoinfo_init);
module_exit(proc_memoinfo_exit);

MODULE_AUTHOR("Mario Alexander Gutierrez Hernandez - 201020781");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A memo_201020781 /proc file.");
