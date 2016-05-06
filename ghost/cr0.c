/* coding: UTF-8 */

/* 检查处理器架构
 *
 * FIXME 只要定义了__KERNEL__，处理器又不是X86，
 *       就必定是X86_64，这是不够的
 */
#ifdef __KERNEL__
# ifdef CONFIG_X86_32
#  define RK_32_BIT
# else
#  define RK_64_BIT
# endif
#else
# ifdef __i386__
#  define RK_32_BIT
# else
#  define RK_64_BIT
# endif
#endif

/*
 * 清除cr0寄存器的写保护位，第16位为WP写保护位
 * 目前仅支持X86、X86_64(又称AMD64、EM64T)架构
 */
unsigned clear_cr0 (void)
{
	unsigned cr0 = 0;
#ifdef __KERNEL__
#ifdef RK_32_BIT
	asm volatile ("movl %%cr0, %%eax"
#endif
#ifdef RK_64_BIT
	asm volatile ("movq %%cr0, %%rax"
#endif
		:"=a" (cr0)
	);
	cr0 &= 0xfffeffff;
#ifdef RK_32_BIT
	asm volatile ("movl %%eax, %%cr0"
#endif
#ifdef RK_64_BIT
	asm volatile ("movq %%rax, %%cr0"
#endif
		:
		:"a" (cr0)
	);
#endif /* __KERNEL__ */
	return cr0;
}

/* 用orig_cr0恢复cr0寄存器 */
void setback_cr0 (unsigned val)
{
#ifdef __KERNEL__
#ifdef RK_32_BIT
	asm volatile ("movl %%eax, %%cr0"
#endif
#ifdef RK_64_BIT
	asm volatile ("movq %%rax, %%cr0"
#endif
		:
		:"a" (val)
	);
#endif /* __KERNEL__ */
}
