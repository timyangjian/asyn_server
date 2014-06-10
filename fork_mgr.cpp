#include "fork_mgr.h"

fork_mgr* g_fork_mgr;

fork_mgr::fork_mgr()
{
	in_parent = true;
}

fork_mgr::~fork_mgr()
{
}
