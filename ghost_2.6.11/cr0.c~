unsigned clear_cr0 (void)
{
	unsigned cr0 = 0;
#ifndef CONFIG_X86_64
	asm volatile ("movl %%eax, %%cr0"
#else
	asm volatile ("movq %%rax, %%cr0"
#endif
		:"=a" (cr0));
	cr0 &= 0xfffeffff;
#ifndef CONFIG_X86_64
	asm volatile ("movl %%eax, %%cr0"
#else
	asm volatile ("movq %%rax, %%cr0"
#endif
		:
		:"a" (cr0));
	return cr0;
}

void setback_cr0 (unsigned val)
{
#ifndef CONFIG_X86_64
	asm volatile ("movl %%eax, %%cr0"
#else
	asm volatile ("movq %%rax, %%cr0"
#endif
		:
		:"a" (val)
	);
}
