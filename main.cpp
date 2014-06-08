#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include "shmq_mgr.h"
#include "fork_mgr.h"
#include "epoll_mgr.h"
#include "dll.h"

bool g_in_parent = true;         
int main(int argc, char* argv[])
{
	register_plugin("./app.so");
	g_shmq_mgr = new shmq_mgr();	
	g_shmq_mgr->create();
	g_fork_mgr = new fork_mgr();
	g_epoll_mgr = new epoll_mgr();

	dll.init_service(g_in_parent);
	int pid = -1;
	if ( (pid = fork ()) < 0 ) {
		printf("fork child process");
		return -1;
	} else if (pid > 0) { //parent process
		g_shmq_mgr->close_pipe();
		g_fork_mgr->set_child_pid(pid);
		//do_add_conn(bc_elem->sendq.pipe_handles[0], fd_type_pipe, 0, bc_elem);
		//net_start(bc_elem->bind_ip, bc_elem->bind_port, bc_elem);
		printf("int parent %d\n", pid);
		sleep(2);
	} else { //child process
		g_in_parent = false;         
		dll.init_service(g_in_parent);
		g_shmq_mgr->close_pipe();
		printf("int child  \n");
		sleep(1);
		//run_worker_process(bc, i, i + 1);
	}

	dll.fini_service(g_in_parent);
	//destroy res
	g_shmq_mgr->destroy();
	return 0;
/*
	if (config_get_strval("addr_mcast_ip")) {
		if (create_addr_mcast_socket() != 0) {
			// return -1 if fail to create mcast socket
			BOOT_LOG(-1, "PARENT: FAILED TO CREATE MCAST FOR RELOADING SO");
		}
	} 
    static int stop_count = 0;
	while (1) {
        if (unlikely(stop == 1 && term_signal == 1 && stop_count++ == 0))
            DEBUG_LOG("SIG_TERM from pid=%d", getpid());
        if (unlikely(stop == 1 && dll.fini_service && (dll.fini_service(1) == 0)))
            break;

        net_loop(-1, page_size, 1);
	}

    killall_children();

	net_exit();
	unregister_data_plugin();
	unregister_plugin();
	shmq_destroy(0, bc->bind_num);
	daemon_stop();
*/
}
