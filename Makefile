## Variables
NAME    = main
SRC     = main.cpp 
OBJ     = $(SRC:.cpp=.o)
# CFLAGS  = -Wall -Werror -Wextra -pedantic -ansi -O3
CFLAGS  = -Wall -Werror -Wextra -pedantic -ansi -O0 -g
LFLAGS    = -lcrypto -lssl
CC        = g++

## Rules
$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(LFLAGS)
all     : $(NAME)
clean   :
	rm -f $(OBJ) $(NAME)
fclean  : clean
	rm -f $(NAME)
re    : fclean all
r    : re
	rm -f *~
	rm -f *.o

# main: main.o
# 	g++ main.o empreinte.o -o main

# main.o: main.cpp
# 	g++ -c main.cpp

# empreinte.o: empreinte.cpp
# 	g++ -c empreinte.cpp

# clean:
# 	rm *.o main
