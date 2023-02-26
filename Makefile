#===============================================================================#
#								SOURCES											#
#===============================================================================#

PARSING_DIR	= parsing
INIT_DIR	= init
KEYHOOK_DIR	= key_hook
MOVE_DIR	= move
DRAW_DIR	= draw
COLOR_DIR	= color
FREE_DIR	= free
MINIMAP_DIR	= minimap

SRC_FILES = $(addprefix $(INIT_DIR)/, init.c init2.c) \
			$(addprefix $(PARSING_DIR)/, parse_map.c parse_map_utils.c set_infos.c valid_map.c) \
			$(addprefix $(KEYHOOK_DIR)/, key_hook.c) \
			$(addprefix $(MOVE_DIR)/, move.c) \
			$(addprefix $(DRAW_DIR)/, draw.c draw_ray.c bresenham.c) \
			$(addprefix $(COLOR_DIR)/, color.c) \
			$(addprefix $(FREE_DIR)/, free.c) \
			$(addprefix $(MINIMAP_DIR)/, minimap.c) \
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
	mkdir $(OBJS_DIR)/$(KEYHOOK_DIR)
	mkdir $(OBJS_DIR)/$(MOVE_DIR)
	mkdir $(OBJS_DIR)/$(DRAW_DIR)
	mkdir $(OBJS_DIR)/$(COLOR_DIR)
	mkdir $(OBJS_DIR)/$(FREE_DIR)
	mkdir $(OBJS_DIR)/$(MINIMAP_DIR)

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