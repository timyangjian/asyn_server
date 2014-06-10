<<<<<<< HEAD

#include "shmq_mgr.h"
=======
#include "shmq_mgr.h"
//
extern bool g_in_parent;         
shmq_mgr* g_shmq_mgr;

shmq_queue::shmq_queue()
{
	len = 1024;
	addr = 0;
	pipe_handles[0] = -1;
	pipe_handles[1] = -1;
}

int shmq_queue::create()
{
	addr = (shm_head_t *) mmap (NULL, len, PROT_READ 
	| PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
	if (addr == MAP_FAILED) {
		printf("mmap failed, %s\n", strerror (errno));
		return -1;
	}

	addr->head = sizeof (shm_head_t);
	addr->tail = sizeof (shm_head_t);
	atomic_set (&(addr->blk_cnt), 0);
	pipe_create ();
	return 0;
}

void shmq_queue::destroy()
{
	if (addr) {
		munmap(addr, len);
		len = 0;
	}
	if (pipe_handles[0] != -1) close(pipe_handles[0]);
	if (pipe_handles[1] != -1) close(pipe_handles[1]);
}

void shmq_queue::close_pipe(int type)
{
	if (type == shmq_queue_type_recv) {
		if (g_in_parent) {
			close(pipe_handles[0]);
		} else {
			close(pipe_handles[1]);
		}
	}
	if (type == shmq_queue_type_send) {
		if (g_in_parent) {
			close(pipe_handles[1]);
		} else {
			close(pipe_handles[0]);
		}
	}
}
>>>>>>> a59ebeaf3cee62e29371d0baa673d2a13c25e321

int shmq_queue::pipe_create()
{
	if (pipe(pipe_handles) == -1) {
		return -1;
	}
<<<<<<< HEAD
	int r_flag = O_NONBLOCK | O_RDONLY | O_NOATIME;
	int w_flag = O_NONBLOCK | O_WRONLY | O_NOATIME;
	fcntl(pipe_handles[0], F_SETFL, r_flag);
	fcntl(pipe_handles[1], F_SETFL, w_flag);
	
	fcntl(pipe_handles[0], F_SETFD, FDCLOEXEC);
	fcntl(pipe_handles[1], F_SETFD, FDCLOEXEC);
=======
	//int r_flag = O_NONBLOCK | O_RDONLY | O_NOATIME;
	//int w_flag = O_NONBLOCK | O_WRONLY | O_NOATIME;

	int r_flag = O_NONBLOCK | O_RDONLY;
	int w_flag = O_NONBLOCK | O_WRONLY;

	fcntl(pipe_handles[0], F_SETFL, r_flag);
	fcntl(pipe_handles[1], F_SETFL, w_flag);
	
	//fcntl(pipe_handles[0], F_SETFD, FDCLOEXEC);
	//fcntl(pipe_handles[1], F_SETFD, FDCLOEXEC);
>>>>>>> a59ebeaf3cee62e29371d0baa673d2a13c25e321
	return 0;
}

int shmq_mgr::create()
{
<<<<<<< HEAD
	q->addr = (shm_head_t *) mmap (NULL, q->length, PROT_READ | PROT_WRITE,
				MAP_SHARED | MAP_ANON, -1, 0);
	if (q->addr == MAP_FAILED) {
		printf("mmap failed, %s", strerror (errno));
		return -1;
	}

	q->addr->head = sizeof (shm_head_t);
	q->addr->tail = sizeof (shm_head_t);
	atomic_set (&(q->addr->blk_cnt), 0);
	pipe_create (q->pipe_handles);
	return 0;

}

int shmq_mgr::pipe_create()
{
}
=======
	if (recv_queue.create() | send_queue.create() != 0) {
		return -1;
	}
	return 0;
}

void shmq_mgr::destroy()
{
	recv_queue.destroy();
	send_queue.destroy();
}

void shmq_mgr::close_pipe()
{
	recv_queue.close_pipe(shmq_queue_type_recv);
	send_queue.close_pipe(shmq_queue_type_send);
}


>>>>>>> a59ebeaf3cee62e29371d0baa673d2a13c25e321
