NAME = Durex
SERVERDIR = ./server
File = 	./server/Auth            \
		./server/Tintin_reporter \
		./server/bonus           \
		./server/daemonize       \
		./server/encrypt         \
		./server/server          \
		./server/utils

CPP_FILE := $(addsuffix .cpp,$(FILE))
O_FILE := $(addsuffix .o,$(FILE))

all: $(NAME)

$(NAME): $(O_FILE) $(CPP_FILE)
	g++ -std=11 $(CPP_FILE) -o $(O_FILE)
	g++ $(O_FILE) -o $(NAME)
clean:
	rm $(O_FILE)
fclean: clean
	rm $(NAME)

# client:
# 	g++ client/client.cpp $(SERVERDIR)/encrypt.cpp -o Ben_AFK
re: clean all

.PHONY: all clean fclean client re
