#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xef025c67, __VMLINUX_SYMBOL_STR(module_layout) },
	{        0, __VMLINUX_SYMBOL_STR(filp_close) },
	{ 0xd62ce0a5, __VMLINUX_SYMBOL_STR(kobject_del) },
	{ 0xc1f2f4d0, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x8cb1ff45, __VMLINUX_SYMBOL_STR(current_task) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x3bf9e5b, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0xc5fdef94, __VMLINUX_SYMBOL_STR(call_usermodehelper) },
	{ 0x2021c348, __VMLINUX_SYMBOL_STR(kobject_add) },
	{ 0xc8995da6, __VMLINUX_SYMBOL_STR(nf_unregister_hooks) },
	{ 0xf0fdf6cb, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{        0, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x5d4d5071, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0x64195a68, __VMLINUX_SYMBOL_STR(nf_register_hooks) },
	{        0, __VMLINUX_SYMBOL_STR(sys_close) },
	{ 0x56fab560, __VMLINUX_SYMBOL_STR(filp_open) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "7BD3F5EBC6452C0B4DF0FC7");
