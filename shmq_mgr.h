#ifndef __SHMQ_MGR_H__
#define __SHMQ_MGR_H__
<<<<<<< HEAD
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
=======
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/mman.h>
#include "atomic.h"

enum {
	shmq_queue_type_recv,
	shmq_queue_type_send,
};

typedef struct shm_head {
	volatile int head;
	volatile int tail;
	atomic_t blk_cnt;
} __attribute__ ((packed)) shm_head_t;

class shmq_queue {
public:
	shmq_queue();
	int create();
	void destroy();
	int pipe_create();
	void close_pipe(int type);
>>>>>>> a59ebeaf3cee62e29371d0baa673d2a13c25e321
public:
	shm_head_t* addr;
	int len;
	int pipe_handles[2];
} ;

class shmq_mgr {
public:
	int create();
<<<<<<< HEAD
};


=======
	void destroy();
	void close_pipe();
private:
	shmq_queue recv_queue;
	shmq_queue send_queue;
};

extern shmq_mgr* g_shmq_mgr;
>>>>>>> a59ebeaf3cee62e29371d0baa673d2a13c25e321
#endif
