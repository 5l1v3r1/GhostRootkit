cmd_/root/ghost/cr0.o := gcc -Wp,-MD,/root/ghost/.cr0.o.d  -nostdinc -isystem /usr/lib/gcc/i386-redhat-linux/4.0.0/include -D__KERNEL__ -Iinclude  -Wall -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -ffreestanding -O2     -fomit-frame-pointer -g -pipe -msoft-float -m32 -fno-builtin-sprintf -fno-builtin-log2 -fno-builtin-puts  -mpreferred-stack-boundary=2 -fno-unit-at-a-time -march=i686 -mtune=pentium4 -mregparm=3 -Iinclude/asm-i386/mach-default -Wdeclaration-after-statement -Wno-pointer-sign   -DMODULE -DKBUILD_BASENAME=cr0 -DKBUILD_MODNAME=ghost -c -o /root/ghost/.tmp_cr0.o /root/ghost/cr0.c

deps_/root/ghost/cr0.o := \
  /root/ghost/cr0.c \
    $(wildcard include/config/x86/64.h) \

/root/ghost/cr0.o: $(deps_/root/ghost/cr0.o)

$(deps_/root/ghost/cr0.o):
