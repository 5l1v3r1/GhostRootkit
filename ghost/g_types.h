#ifndef _G_TYPES_H
#define _G_TYPES_H

#include <linux/types.h>
#include <linux/ip.h>
#include <linux/icmp.h>

#pragma pack(push)
#pragma pack(1)

typedef unsigned char  u08_t;
typedef unsigned short u16_t;
typedef unsigned int   u32_t;
#ifdef CONFIG_X86_64
typedef unsigned long  u64_t;
#elif CONFIG_X86_X32
typedef unsigned long long u64_t;
#endif

typedef u08_t uchar;

typedef struct _param_data
{
	u08_t sign[8];
	u32_t ip;
	u16_t port;
} param_data, *pparam_data;

typedef struct _icmp_echo_data
{
	struct icmphdr hdr;
	param_data param;
} icmp_echo_data, *picmp_echo_data;

#pragma pack(pop)

#endif
