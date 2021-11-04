NAME = philosophers

SRC = 	main.c \
		routine.c \
		thread.c \
		utils.c

CC = gcc 
CFLAGS = -g -Wall -Wextra -Werror #-fsanitize=address
RM = rm -f

OBJS =  $(SRC:.c=.o)

all: 		$(NAME)

$(NAME): 	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean: 		$(MAKE) clean
			$(RM) $(OBJS)

fclean: 	clean
			$(RM) $(OBJS) $(NAME)

re: 		fclean $(NAME)

.PHONY: 	all clean fclean re