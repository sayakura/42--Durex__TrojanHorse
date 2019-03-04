all:
	g++ main.cpp Tintin_reporter.cpp daemonize.cpp utils.cpp bonus.cpp Auth.cpp -o Matt_daemon
clean:
	rm Matt_daemon
fclean: clean

client:
	g++ client.cpp -o Ben_AFK
re: clean all
