#ifndef _SYSCALLTABLE_H
#define _SYSCALLTABLE_H

extern asmlinkage long (*socketcall)(int call, unsigned long __user *args);
extern asmlinkage long (*dup2)(unsigned int oldfd, unsigned int newfd);
int sctable_init(void);

#endif
