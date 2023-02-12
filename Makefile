#===============================================================================#
#								SOURCES											#
#===============================================================================#

PARSING_DIR	= parsing
INIT_DIR	= init
MAP_DIR		= $(PARSING_DIR)/map
MOVE_DIR	= move
DRAW_DIR	= draw
COLOR_DIR	= color
FREE_DIR	= free

SRC_FILES = $(addprefix $(INIT_DIR)/, init.c) \
			$(addprefix $(MAP_DIR)/, parse_map.c parse_map_utils.c set_infos.c valid_map.c) \
			$(addprefix $(MOVE_DIR)/, movements.c) \
			$(addprefix $(DRAW_DIR)/, draw.c) \
			$(addprefix $(COLOR_DIR)/, color.c) \
			$(addprefix $(FREE_DIR)/, free.c) \
			main.c print.c

 #=============================================================================#
#									OBJETS										#
 #=============================================================================#

OBJS_DIR = objects
OBJS = $(SRC_FILES:%.c=$(OBJS_DIR)/%.o)
DEPS = $(SRC_FILES:%.c=$(OBJS_DIR)/%.d)

 #=============================================================================#
#									LIBRARY										#
 #=============================================================================#

LIB_DIR = libft

 #=============================================================================#
#									COMPILATION									#
 #=============================================================================#

CC = cc
CFLAGS = -g3 #-Wall -Wextra -Werror
CDFLAGS = -MMD -MP
CIFLAGS = -Iincludes -I$(LIB_DIR)/includes
CLFLAGS = -L$(LIB_DIR) -lft
MLX_DIR = mlx
MLX = $(MLX_DIR)/libmlx.a
MLXFLAGS = -L. -lXext -lX11 -lm

 #=============================================================================#
#									MAKEFILE									#
 #=============================================================================#

NAME = cub3d

all : $(NAME)

$(NAME) : $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(CIFLAGS) $(OBJS) $(CLFLAGS) $(MLX) $(MLXFLAGS) -o $(NAME)

$(MLX):
		$(MAKE) -C $(MLX_DIR)

$(OBJS_DIR) :
	$(MAKE) -C $(LIB_DIR)
	mkdir $(OBJS_DIR)
	mkdir $(OBJS_DIR)/$(PARSING_DIR)
	mkdir $(OBJS_DIR)/$(INIT_DIR)
	mkdir $(OBJS_DIR)/$(MAP_DIR)
	mkdir $(OBJS_DIR)/$(MOVE_DIR)
	mkdir $(OBJS_DIR)/$(DRAW_DIR)
	mkdir $(OBJS_DIR)/$(COLOR_DIR)
	mkdir $(OBJS_DIR)/$(FREE_DIR)

$(OBJS) : $(OBJS_DIR)/%.o : %.c
	$(CC) $(CFLAGS) $(CDFLAGS) $(CIFLAGS) -c $< -o $@

clean :
	$(MAKE) clean -C $(LIB_DIR)
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIB_DIR)
	rm -rf $(NAME)

re : fclean all

-include $(DEPS)

.PHONY: all clean fclean re

#.SILENT: