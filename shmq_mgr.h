#ifndef __SHMQ_MGR_H__
#define __SHMQ_MGR_H__
#include <stdint.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

struct shm_head {
	volatile int head;
	volatile int tail;
	atomic_t blk_cnt;
} shm_head_t;

class shmq_queue {
public:
	void pipe_create();
public:
	shm_head_t* addr;
	int len;
	int pipe_handles[2];
} ;

class shmq_mgr {
public:
	int create();
};


#endif
