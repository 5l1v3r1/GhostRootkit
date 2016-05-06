#ifndef _NETFILTER_HOOK_H
#define _NETFILTER_HOOK_H
#include "g_types.h"

void nf_reg_hook(void);
void nf_reg_unhook(void);

extern bool rshell;
extern picmp_echo_data icmpdata;
#endif
