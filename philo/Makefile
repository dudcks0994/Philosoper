NAME = philo
CC = cc
CFLAGS = -Werror -Wall -Wextra
SRCS = main.c philo.c utils.c
SRC_OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(SRC_OBJS)
	$(CC) $^ -o $@

%.o : %.c
	$(CC)  $(CFLAGS) -c $<

re : fclean all

clean : 
	rm -f $(SRC_OBJS)

fclean : clean
	rm -f $(NAME)

.PHONY : all re clean fclean
