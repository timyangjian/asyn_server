#ifndef __EPOLL_MGR__
#define __EPOLL_MGR__
#include <stdint.h>
#define __IS_LINUX__ 0
class connection_mgr;

enum {
	max_fd_num = 1000,
};
class epoll_mgr {
public:
	epoll_mgr();
public:
	int create();
	int add_in_event(int& new_fd);
	int mod_in_event(int& fd);
	int mod_in_out_event(int& fd);
	int del_event(int& fd);
	
	int epoll_wait();
private:
	int on_close(int& fd);
	int on_ready_read_data();
	int on_ready_write_data();
private:
	int m_epoll_fd;

#if __IS_LINUX__
	struct epoll_event m_ev;
	int m_max_event;
	struct epoll_event* m_events;
#endif
	connection_mgr* conn_mgr;
};


extern epoll_mgr* g_epoll_mgr;

#endif
