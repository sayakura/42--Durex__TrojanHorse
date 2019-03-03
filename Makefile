all:
	g++ main.cpp Tintin_reporter.cpp daemonize.cpp

clean:
	rm ./var/lock/matt_daemon.lock
	rm ./var/log/matt_daemon/matt-daemon.log
