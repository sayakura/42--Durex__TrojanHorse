SERVERDIR = ./server
all:
	g++ $(SERVERDIR)/main.cpp $(SERVERDIR)/Tintin_reporter.cpp $(SERVERDIR)/daemonize.cpp $(SERVERDIR)/utils.cpp $(SERVERDIR)/bonus.cpp $(SERVERDIR)/Auth.cpp  $(SERVERDIR)/encrypt.cpp -o Matt_daemon
clean:
	rm Matt_daemon Ben_AFK
fclean: clean

client:
	g++ client/client.cpp $(SERVERDIR)/encrypt.cpp -o Ben_AFK
re: clean all

.PHONY: all clean fclean client re
