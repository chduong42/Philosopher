# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chduong <chduong@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/05 18:48:08 by kennyduong        #+#    #+#              #
#    Updated: 2021/12/27 16:57:42 by chduong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#########################################
#				PROGRAMS				#
#########################################
SL			=	philosopher

#########################################
#				COMMANDS				#
#########################################
CC			=	clang
MKDIR		=	mkdir -p
AR			=	ar rcs
RM			= 	rm -rf

#########################################
#				COLORS					#
#########################################
GREY       =   $'\033[0;30m
RED        =   $'\033[0;31m
GREEN      =   $'\033[0;92m
YELLOW     =   $'\033[0;33m
BLUE       =   $'\033[0;34m
U_BLUE     =   $'\033[4;34m
PURPLE     =   $'\033[0;35m
CYAN       =   $'\033[0;96m
WHITE      =   $'\033[0;37m
END        =   $'\033[0;m
BOLD       =   $'\e[1m

#########################################
#			FLAGS COMPILATION			#
#########################################
CFLAGS		=	-Wall -Wextra -Werror
DEBUG		=	-fsanitize=address -g3

INC			= 	-I includes $(INC_MLX) $(INC_LFT)
INC_LFT		=	-I libft/inc

LINK		=	$(LINK_LFT) $(LINK_MLX)
LINK_LFT	=	-L ./libft -lft

#########################################
#			DIRECTORIES					#
#########################################
SRC_DIR		=	srcs/
LFT_DIR		=	libft/
OBJ_DIR		=	obj/

#########################################
#			SOURCES	FILES				#
#########################################
LIBFT		=	$(LFT_DIR)libft.a

PH_SRC		=	

#########################################
#            OBJECT FILES    	        #
#########################################
PH_OBJ		=	$(PH_SRC:.c=.o)
PH_OBJ		:=	$(addprefix $(OBJ_DIR), $(PH_OBJ))

#########################################
#			MAKE	RULES				#
#########################################
$(SL): $(MLX) $(LIBFT) $(OBJ_DIR) $(SL_OBJ)
	@echo "> $(CYAN)Generate objects$(END) : \t\t[$(GREEN)OK$(END)]"
	@$(CC) -o $@ $(SL_OBJ) $(LIBFT) $(MLX) $(LINK)
	@echo "> $(WHITE)$(BOLD)Philosopher Compilation$(END) : \t[$(YELLOW)COMPLETE$(END)]"

$(LIBFT):
	@make -s -C $(LFT_DIR)
	@echo "> $(CYAN)Create LIBFT$(END) : \t\t[$(GREEN)OK$(END)]"

${OBJ_DIR}%.o:	${SRC_DIR}%.c
# @${MKDIR} ${@D}
	@${CC} ${CFLAGS} ${INC} -c -o $@ $<

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)
	
all: $(SL)

bonus :	
	
clean:
	@$(RM) $(OBJ_DIR)
	@make -s -C $(LFT_DIR) clean
	@echo "> $(PURPLE)Clean objects$(END) : \t\t[$(GREEN)OK$(END)]"
	
fclean: clean
	@make -s -C $(LFT_DIR) fclean
	@echo "> $(PURPLE)Delete LIBFT$(END) : \t\t[$(GREEN)OK$(END)]"
	@$(RM) $(SL)
	@echo "> $(PURPLE)Delete Program$(END) : \t\t[$(GREEN)OK$(END)]"
	
re: fclean all 

norm:
	@norminette ${SRC_DIR} ${INC_DIR} | grep 'Error' ; true

leak:
	valgrind ./${SL}

.PHONY: all clean fclean re