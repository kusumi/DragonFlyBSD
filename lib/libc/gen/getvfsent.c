/*
 * getvfsent.c - get a listing of installed filesystems
 * Written September 1994 by Garrett A. Wollman
 * This file is in the public domain.
 *
 * $FreeBSD: src/lib/libc/gen/getvfsent.c,v 1.14.2.1 2001/03/05 09:19:38 obrien Exp $
 */

#include <sys/param.h>
#include <sys/linker.h>
#include <sys/mount.h>
#include <sys/sysctl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* XXX hide some compatibility problems. */
#undef getvfsbyname

static struct ovfsconf *_vfslist = NULL;
static struct ovfsconf _vfsconf;
static size_t _vfslistlen = 0;
static int _vfs_keeplist = 0;
static size_t _vfs_index = 0;

static int
initvfs(void)
{
	int mib[2] = { CTL_VFS, VFS_VFSCONF };
	size_t size = 0;
	int rv;

	rv = sysctl(mib, 2, NULL, &size, NULL, (size_t)0);
	if(rv < 0)
		return 0;

	if(_vfslist)
		free(_vfslist);
	_vfslist = malloc(size);
	if(!_vfslist)
		return 0;

	rv = sysctl(mib, 2, _vfslist, &size, NULL, (size_t)0);
	if(rv < 0) {
		free(_vfslist);
		_vfslist = NULL;
		return 0;
	}

	_vfslistlen = size / sizeof(_vfslist[0]);
	return 1;
}

struct ovfsconf *
getvfsent(void)
{
	if(!_vfslist && !initvfs())
		return 0;

	do {
		if(_vfs_index >= _vfslistlen)
			return 0;

		_vfsconf = _vfslist[_vfs_index++];
	} while(!_vfsconf.vfc_vfsops);

	if(!_vfs_keeplist) {
		free(_vfslist);
		_vfslist = NULL;
	}
	return &_vfsconf;
}

struct ovfsconf *
getvfsbyname(const char *name)
{
	size_t i;

	if(!_vfslist && !initvfs())
		return 0;

	for(i = 0; i < _vfslistlen; i++) {
		if( ! strcmp(_vfslist[i].vfc_name, name) )
			break;
	}

	if(i < _vfslistlen)
		_vfsconf = _vfslist[i];

	if(!_vfs_keeplist) {
		free(_vfslist);
		_vfslist = NULL;
	}

	if(i < _vfslistlen)
		return &_vfsconf;
	else
		return 0;
}

struct ovfsconf *
getvfsbytype(int type)
{
	size_t i;

	if(!_vfslist && !initvfs())
		return 0;

	for(i = 0; i < _vfslistlen; i++) {
		if(_vfslist[i].vfc_index == type)
			break;
	}

	if(i < _vfslistlen)
		_vfsconf = _vfslist[i];

	if(!_vfs_keeplist) {
		free(_vfslist);
		_vfslist = NULL;
	}

	if(i < _vfslistlen)
		return &_vfsconf;
	else
		return 0;
}

void
setvfsent(int keep)
{
	if(_vfslist && !keep) {
		free(_vfslist);
		_vfslist = NULL;
	}

	_vfs_keeplist = keep;
	_vfs_index = 0;
}

void
endvfsent(void)
{
	if(_vfslist) {
		free(_vfslist);
		_vfslist = NULL;
	}

	_vfs_index = 0;
}

int
vfsisloadable(const char *name __unused)
{
	return 1;
}

int
vfsload(const char *name)
{
	int status;

	status = kldload(name);
	return status == -1 ? status : 0;
}
