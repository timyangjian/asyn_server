#ifndef __DLL_H__
#define __DLL_H__

class conn_handle;
#ifdef __cplusplus
extern "C" {
#endif
#include <sys/types.h>

/**
 * @struct AsyncServInterface
 * @brief To make use of AsyncServ, a .so must implement the interfaces held by this structure
 *
 */
typedef struct AsyncServInterface {
	void*   handle; // Hold the handle returned by dlopen

	/* The following 5 interfaces are called only by the child process */
	void	(*proc_events)();
	int		(*proc_pkg_from_client)(void* pkg, int pkglen, conn_handle* handle);
	void	(*proc_pkg_from_serv)(int fd, void* pkg, int pkglen);
	/*! Called each time when a client close a connection, or when `proc_pkg_from_client` returns -1. */
	void	(*on_client_conn_closed)(int fd);
	/*! Called each time on close of the FDs opened by the child. */
	void	(*on_fd_closed)(int fd);

	/* The following 3 interfaces are called both by the parent and child process */

	/*!
	  * Called only once at server startup by both the parent and child process. Optional interface.\n
	  * You must return 0 on success, -1 otherwise.
	  */
	int 	(*init_service)(bool);
	/*!
	  * Called only once at server stop by both the parent and child process. Optional interface.\n
	  */
	int 	(*fini_service)(bool);
	/*!
	  * This interface will be called both by the parent and child process.\n
	  * You must return 0 if you cannot yet determine the length of the incoming package,
	  * return -1 if you find that the incoming package is invalid and AsyncServ will close the connection,
	  * otherwise, return the length of the incoming package. Note, the package should be no larger than 8192 bytes.
	  */
	int		(*get_pkg_len)(int fd, const void* avail_data, int avail_len, int isparent);

} dll_info_t;

extern dll_info_t dll;

/**
  * @brief get name of the server
  * @return name that is specified at the second column of 'bind.conf'
  */
static inline const char* get_server_name()
{
	return 0;
}

int  register_plugin(const char* file_name);
void unregister_plugin();

#ifdef __cplusplus
} // end of extern "C"
#endif

#endif // __DLL_H__
