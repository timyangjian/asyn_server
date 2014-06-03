class connection_mgr;

class epoll_mgr {
public:
	epoll_mgr();
public:
	int add_in_event(int& new_fd);
	int mod_in_event(int& fd);
	int mod_in_out_event(int& fd);
	int del_event(int& fd);

	int epoll_wait();
private:
	int epoll_create();
	int on_close(int& fd);
	int on_ready_read_data();
	int on_ready_write_data();
private:
	int m_epoll_fd;
	struct epoll_event m_ev;
	int m_max_event;
	struct epoll_event* m_events;
	connection_mgr* conn_mgr;
};
