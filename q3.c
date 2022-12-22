#include <linux/module.h>  
#include <linux/kernel.h>  
#include <linux/sched.h>
#include <linux/sched/signal.h>

static int pid = 3;
module_param(pid,int,0644);

static int __init process_info_init(void)
{
    struct task_struct *task = current;
    for_each_process(task){
        if(task->pid == pid){
            printk(KERN_INFO "Process ID: %d\n", task->pid);
            printk(KERN_INFO "Command: %s\n", task->comm);
            printk(KERN_INFO "User ID: %d\n", task->state);
            printk(KERN_INFO "Group ID: %d\n",task->group_leader->pid);
        }
    }
    return 0;
}


static void __exit process_info_exit(void)
{
    
}


module_init(process_info_init);
module_exit(process_info_exit);


MODULE_AUTHOR("Lakshya Kumar");
MODULE_LICENSE("GPL");
