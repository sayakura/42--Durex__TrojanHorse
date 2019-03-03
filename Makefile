all:
	g++ main.cpp Tintin_reporter.cpp daemonize.cpp -o Matt_daemon
clean:
	rm Matt_daemon
fclean: re

re:
