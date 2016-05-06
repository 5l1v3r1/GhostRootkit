#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

#undef unix
struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = __stringify(KBUILD_MODNAME),
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
};

static const struct modversion_info ____versions[]
__attribute_used__
__attribute__((section("__versions"))) = {
	{ 0x6d134bc3, "struct_module" },
	{ 0x283190c, "filp_close" },
	{ 0xe6758556, "nf_register_hook" },
	{ 0x44b9c4c8, "kobject_del" },
	{ 0x1b7d4074, "printk" },
	{ 0x18c83616, "kthread_stop" },
	{ 0x436006da, "call_usermodehelper" },
	{ 0x17d59d01, "schedule_timeout" },
	{ 0x27330e0c, "wake_up_process" },
	{ 0xd2965f6f, "kthread_should_stop" },
	{ 0x52c722a8, "nf_unregister_hook" },
	{ 0xf224d33c, "kthread_create" },
	{ 0x268cc6a2, "sys_close" },
	{ 0x2f67b2f2, "filp_open" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "79D2A1D15925DD2EFDCA176");
