obj-m := ghost.o
ghost-objs := ghost_main.o cr0.o syscalltable.o netfilter_hook.o shellutil.o vfs_hook.o
KDIR := /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
