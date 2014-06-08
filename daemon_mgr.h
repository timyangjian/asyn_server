#ifndef __DAEMON_MGR_H__
#define __DAEMON_MGR_H__
#include "const_type.h"
#include "atomic.h"

class daemon_mgr {
public:
private:
	atomic_t child_pids[max_listen_];
};

#endif
