all:
	g++ -std=11 main.cpp Tintin_reporter.cpp daemonize.cpp utils.cpp -o Matt_daemon
clean:
	rm Matt_daemon
fclean: re

re:
