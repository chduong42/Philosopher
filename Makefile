# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/05 18:48:08 by kennyduong        #+#    #+#              #
#    Updated: 2022/01/18 00:40:28 by kennyduong       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#########################################
#				PROGRAMS				#
#########################################
PH			=	philo

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
BOLD       =   $'\033[1m

#########################################
#			FLAGS COMPILATION			#
#########################################
CFLAGS		=	-Wall -Wextra -Werror -pthread
DEBUG		=	-fsanitize=thread -g3
INC			= 	-I includes
LINK		= 	-pthread

#########################################
#			DIRECTORIES					#
#########################################
SRC_DIR		=	srcs/
OBJ_DIR		=	obj/

#########################################
#			SOURCES	FILES				#
#########################################
PH_SRC		=	main.c			create_threads.c		parsing.c\
				routine.c		utils.c					utils2.c

#########################################
#            OBJECT FILES    	        #
#########################################
PH_OBJ		=	$(PH_SRC:.c=.o)
PH_OBJ		:=	$(addprefix $(OBJ_DIR), $(PH_OBJ))

#########################################
#			MAKE	RULES				#
#########################################
all: $(PH)

$(PH): $(OBJ_DIR) $(PH_OBJ)
	@echo "> $(CYAN)Generate objects$(END) : \t\t[$(GREEN)OK$(END)]"
	@$(CC) $(LINK) -o $@ $(PH_OBJ)
	@echo "> $(WHITE)$(BOLD)Philosopher Compilation$(END) : \t[$(YELLOW)COMPLETE$(END)]"

${OBJ_DIR}%.o:	${SRC_DIR}%.c
# @${MKDIR} ${@D}
	@${CC} ${CFLAGS} ${INC} -c -o $@ $<

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)

bonus :	
	
clean:
	@$(RM) $(OBJ_DIR)
	@echo "> $(PURPLE)Clean objects$(END) : \t\t[$(GREEN)OK$(END)]"
	
fclean: clean
	@$(RM) $(PH)
	@echo "> $(PURPLE)Delete Program$(END) : \t\t[$(GREEN)OK$(END)]"
	
re: fclean all 

norm:
	@norminette ${SRC_DIR} ${INC_DIR} | grep 'Error' ; true

leak:
	valgrind ./${PH}

.PHONY: all clean fclean re