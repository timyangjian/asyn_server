epoll_mgr::epoll_mgr()
{
	m_max_event = 1000;
	m_events = (struct epoll_event*)malloc(sizeof(struct epoll_event) * m_max_event);
}

int epoll_mgr::add_in_event(int& new_fd)
{
	m_ev.events = EPOLLIN | EPOLLET;
	m_ev.data.fd = new_fd;
	if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, new_fd, &m_ev) < 0) {
		return -1;
	}
	return 0;
}

int epoll_mgr::mod_in_event(int& fd)
{
	m_ev.events = EPOLLIN | EPOLLET;
	m_ev.data.fd = fd;
	if (epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, fd, &m_ev) < 0) {
		return -1;
	}
	return 0;
}

int epoll_mgr::mod_in_out_event(int& fd)
{
	m_ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
	m_ev.data.fd = fd;
	if (epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, fd, &m_ev) < 0) {
		return -1;
	}
	return 0;
}

int epoll_mgr::del_event(int& fd)
{
	m_ev.data.fd = fd;
	if (epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, fd, &m_ev) < 0) {
		return -1;
	}
	return 0;
}

int epoll_mgr::on_close(int& fd)
{
	conn_mgr->del_conn(fd);
	del_event(fd);
}

int epoll_mgr::on_ready_read_data()
{
}

int epoll_mgr::on_ready_write_data()
{
}


int epoll_wait()
{
	int nfds = epoll_wait(m_epoll_fd, m_events, m_max_event, -1);
    for(i = 0; i < nfds ; ++i) {
/*
		if(events.data.fd == listenfd) {
				printf("LISTENFD\n");
				socklen_t clilen= sizeof(struct sockaddr);
				struct sockaddr_in clientaddr;
				int sign = 1;
				while((connfd = accept(listenfd,(struct sockaddr *)&clientaddr,&clilen)) < 0) {
					if(errno == EINTR)
						continue;
					if(errno != EAGAIN && errno != EWOULDBLOCK)
					{
						printf("errno != EAGAIN\n");
						sign = 0;
						break;
					}
				}
				printf("%d END LISTENFD\n",connfd);
				if(sign == 1)
				{
						if(setnonblocking(connfd))
						{
								printf("setnonblocking connfd\n");
						}
						struct epoll_event ev;
						char *str = inet_ntoa(clientaddr.sin_addr);
						printf("accapt a connection from:%s\n",str);
						ev.data.u64 = 0UL;
						ev.data.fd = connfd;
						ev.events = EPOLLIN | EPOLLONESHOT | EPOLLHUP | EPOLLERR | EPOLLRDHUP;
						epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);
				}
			}
*/
			} else if(m_events[i].events & EPOLLRDHUP) {
				//printf("sockt closed by peer EPOLLRDHUP\n");
				//while (close(events.data.fd) < 0 && errno == EINTR) {};
			} else if(m_events[i].events & EPOLLHUP) {
				//printf("sockt closed by peer EPOLLHUP\n");
				//while (close(events.data.fd) < 0 && errno == EINTR) {};
			} else if(m_events[i].events & EPOLLERR) {
				//printf("sockt closed by peer EPOLLERR\n");
				//epoll_ctl(epfd,EPOLL_CTL_DEL,events.data.fd,&ev);
			} else if(m_events[i].events & EPOLLIN) {
				printf("EPOLLIN\n");
				if (on_ready_read_data() == -1) {
					on_close(m_events[i].data.fd);
				}
			} else if(m_events[i].events & EPOLLOUT) {
				printf("EPOLLOUT\n");
				on_ready_write_data();
			}  else {
				while (close(events.data.fd) < 0 && errno == EINTR) {};
			}

		}
	
	}
}



