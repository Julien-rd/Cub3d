NAME = cub3d
INC_DIR = includes
CFLAGS = -Wall -Wextra -Werror -Ilibft -MMD -g -I$(INC_DIR)
OBJ_DIR = obj
VPATH = parsing
SRC = main.c parse_map.c read_file_to_string.c


OBJ = $(SRC:%.c=obj/%.o)
DEP = $(SRC:%.c=obj/%.d)
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

.SILENT:

all: $(NAME)

$(LIBFT):
	$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -MF $(@:.o=.d) -c $< -o $@

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline 2>&1

clean: 
	rm -f $(OBJ) $(DEP)
	rm -rf $(OBJ_DIR)
	$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re
