#ifndef __SHMQ_MGR_H__
#define __SHMQ_MGR_H__
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
public:
	shm_head_t* addr;
	int len;
	int pipe_handles[2];
} ;

class shmq_mgr {
public:
	int create();
	void destroy();
	void close_pipe();
private:
	shmq_queue recv_queue;
	shmq_queue send_queue;
};

extern shmq_mgr* g_shmq_mgr;
#endif
