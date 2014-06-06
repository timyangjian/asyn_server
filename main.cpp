#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
             
bool inParent = true;         
int main(int argc, char* argv[])
{
	//net_init
	
	g_shmq_mgr->create();
		shmq_create(bc_elem);

		if ( (pid = fork ()) < 0 ) {
			BOOT_LOG(-1, "fork child process");
		} else if (pid > 0) { //parent process
			close_shmq_pipe(bc, i, 0);
			do_add_conn(bc_elem->sendq.pipe_handles[0], fd_type_pipe, 0, bc_elem);
			net_start(bc_elem->bind_ip, bc_elem->bind_port, bc_elem);
            atomic_set(&child_pids[i], pid);
		} else { //child process
			g_listen_port = bc_elem->bind_port;
			strncpy(g_listen_ip, bc_elem->bind_ip, sizeof(g_listen_ip) - 1);
			run_worker_process(bc, i, i + 1);
		}
	}

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

	return 0;
}
