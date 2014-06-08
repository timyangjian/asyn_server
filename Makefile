bin = ../new_async_test/main
cc = g++
cflags = -Wall -g
obj = main.o shmq_mgr.o fork_mgr.o dll.o epoll_mgr.o
cpp = main.cpp shmq_mgr.cpp fork_mgr.cpp dll.cpp epoll_mgr.cpp

$(bin): $(obj)
	$(cc) $(cflags) -o $(bin) $(obj)
$(obj): $(cpp)
	$(cc) $(cflags) -c $(cpp)

.PHONY: clean
clean:
	-rm $(bin) $(obj)
