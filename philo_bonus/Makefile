NAME = philo_bonus
CC = cc
CFLAGS = -Werror -Wall -Wextra -pthread
SRCS = 	main_bonus.c etc_utils_bonus.c drop_fork_bonus.c init_utils_bonus.c \
		print_utils_bonus.c return_utils_bonus.c thread_utils_bonus.c
SRC_OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(SRC_OBJS)
	$(CC) $^ -o $@

%.o : %.c
	$(CC) -c $<

re : fclean all

clean : 
	rm -f $(SRC_OBJS)

fclean : clean
	rm -f $(NAME)

.PHONY : all re clean fclean
