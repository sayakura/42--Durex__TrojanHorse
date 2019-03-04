all:
	g++ main.cpp Tintin_reporter.cpp daemonize.cpp utils.cpp bonus.cpp Auth.cpp -o Matt_daemon
clean:
	rm Matt_daemon
fclean: re

re:
