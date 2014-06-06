
#include "shmq_mgr.h"

int shmq_queue::pipe_create()
{
	if (pipe(pipe_handles) == -1) {
		return -1;
	}
	int r_flag = O_NONBLOCK | O_RDONLY | O_NOATIME;
	int w_flag = O_NONBLOCK | O_WRONLY | O_NOATIME;
	fcntl(pipe_handles[0], F_SETFL, r_flag);
	fcntl(pipe_handles[1], F_SETFL, w_flag);
	
	fcntl(pipe_handles[0], F_SETFD, FDCLOEXEC);
	fcntl(pipe_handles[1], F_SETFD, FDCLOEXEC);
	return 0;
}

int shmq_mgr::create()
{
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
