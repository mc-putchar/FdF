# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 19:09:15 by mcutura           #+#    #+#              #
#    Updated: 2023/06/12 22:04:33 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
#--- DIRECTORIES ---
SRCDIR := src
INCDIR := inc
OBJDIR := obj
LIBFTDIR := libft
LIBMLXDIR := libmlx
#--- LIBRARIES ---
LIBFT := $(LIBFTDIR)/libft.a
LIBMLX := $(LIBMLXDIR)/libmlx_Linux.a
#--- SOURCES ---
SRCS := $(addprefix $(SRCDIR)/, main.c error_handler.c parse_map.c ft_image.c \
	ft_window.c draw_map.c projection.c hooks.c fdf_utils.c colors.c)
#--- OBJECTS ---
OBJS := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
#--- HEADERS ---
HEADERS := $(addprefix $(INCDIR)/, fdf.h ft_window.h libft.h get_next_line.h \
			ft_printf.h ft_image.h keycodes.h error_handler.h)
MLXHEADER := /usr/local/include
#--- FLAGS ---
CFLAGS := -Wall -Wextra -Werror -I$(INCDIR)
LDFLAGS := -L$(LIBFTDIR) -L$(LIBMLXDIR)
LDLIBS := -lft -lmlx
LFLAGS := -lbsd -lXext -lX11 -lm

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(HEADERS) $(MLXHEADER) $(LIBFT) $(LIBMLX) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDLIBS) $(LFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(LIBMLX):
	$(MAKE) -C $(LIBMLXDIR)

$(HEADERS):
	ln $(LIBFTDIR)/libft.h $(INCDIR)/libft.h
	ln $(LIBFTDIR)/get_next_line.h $(INCDIR)/get_next_line.h
	ln $(LIBFTDIR)/ft_printf.h $(INCDIR)/ft_printf.h

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(LIBMLXDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(INCDIR)/libft.h
	$(RM) $(INCDIR)/get_next_line.h
	$(RM) $(INCDIR)/ft_printf.h
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all
