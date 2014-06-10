#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <stdio.h>
#include "dll.h"

dll_info_t dll;

#define DLFUNC(h, v, name) \
		do { \
			v = dlsym (h, name); \
			if ((error = dlerror ()) != NULL) { \
				ERROR_LOG("dlsym error, %s", error); \
				dlclose(h); \
				h = NULL; \
				goto out; \
			} \
		} while (0)

void* dll_func_no_error(void* handle, const char* name)
{
	void* ret = dlsym(handle, name);
	dlerror();
	return ret;
}

void* dll_func(void* handle, const char* name)
{
	char* error; 
	void* ret = dlsym(handle, name);
	error = dlerror();
	if (error != NULL) {
		printf("dlsym error, %s\n", error);
		dlclose(handle);
		return 0;
	}
	return ret;
}

#define DLFUNC_NO_ERROR(h, name) \
	dll. ##name = (typeof(dll. ##name))dll_func_no_error(dll.handle, #name);

int register_plugin(const char* file_name)
{
	char* error; 
	int   ret_code = -1;
	
	dll.handle = dlopen(file_name, RTLD_NOW);
	if ((error = dlerror()) != NULL) {
		printf("dlopen error, %s\n", error);
		goto out;
	}
	
	dll.init_service = (typeof(dll.init_service))dll_func(dll.handle, "init_service");
	dll.fini_service = (typeof(dll.fini_service))dll_func(dll.handle, "fini_service");
	dll.proc_events = (typeof(dll.proc_events))dll_func(dll.handle, "proc_events");

	dll.get_pkg_len = (typeof(dll.get_pkg_len))dll_func(dll.handle, "get_pkg_len");
	dll.proc_pkg_from_client = 
		(typeof(dll.proc_pkg_from_client))dll_func(dll.handle, "proc_pkg_from_client");
	dll.proc_pkg_from_serv = (typeof(dll.proc_pkg_from_serv))dll_func(dll.handle, "proc_pkg_from_serv");
	dll.on_client_conn_closed = 
		(typeof(dll.on_client_conn_closed))dll_func(dll.handle, "on_client_conn_closed");
	dll.on_fd_closed = (typeof(dll.on_fd_closed))dll_func(dll.handle, "on_fd_closed");

	ret_code = 0;

out:
	printf("%d...dlopen %s\n", ret_code, file_name);
	return ret_code;
}

void unregister_plugin()
{
	if (dll.handle != NULL){
		dlclose(dll.handle);
		dll.handle = NULL;
	}
}

