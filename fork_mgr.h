#ifndef __FORK_MGR_H__
#define __FORK_MGR_H__
#include "atomic.h"

class fork_mgr {
public:
	fork_mgr();
	~fork_mgr();
	void set_in_child() {
		in_parent = false;
	}
	void set_child_pid(int in_pid) { 
		atomic_set(&child_pid, in_pid);
	}
	bool is_in_parent() { return in_parent; }
	bool is_in_child() { return !is_in_parent(); }
private:
 bool in_parent;
 atomic_t child_pid;
};

extern fork_mgr* g_fork_mgr;
#endif

