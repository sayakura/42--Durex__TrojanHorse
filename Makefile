SERVERDIR = ./server
all:
<<<<<<< HEAD
	g++ -std=11 main.cpp Tintin_reporter.cpp daemonize.cpp utils.cpp -o Matt_daemon
=======
	g++ $(SERVERDIR)/main.cpp $(SERVERDIR)/Tintin_reporter.cpp $(SERVERDIR)/daemonize.cpp $(SERVERDIR)/utils.cpp $(SERVERDIR)/bonus.cpp $(SERVERDIR)/Auth.cpp  $(SERVERDIR)/encrypt.cpp -o Matt_daemon
>>>>>>> 3faa47e576020f29ceab8a4ebad44a031804b0cf
clean:
	rm Matt_daemon Ben_AFK
fclean: clean

client:
	g++ client/client.cpp $(SERVERDIR)/encrypt.cpp -o Ben_AFK
re: clean all

.PHONY: all clean fclean client re
