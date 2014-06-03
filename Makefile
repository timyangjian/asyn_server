bin = main
cc = g++
cflags = -Wall -g
obj = main.o dsocket.o depoll.o
cpp = main.cpp dsocket.cpp depoll.cpp

$(bin): $(obj)
	$(cc) $(cflags) -o $(bin) $(obj)
$(obj): $(cpp)
	$(cc) $(cflags) -c $(cpp)

.PHONY: clean
clean:
	-rm $(bin) $(obj)
