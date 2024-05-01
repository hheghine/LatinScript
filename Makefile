LINE_COLORS_1 = \033[38;2;204;0;51m
LINE_COLORS_2 = \033[38;2;153;0;102m
LINE_COLORS_3 = \033[38;2;101;0;153m
LINE_COLORS_4 = \033[38;2;89;0;165m
LINE_COLORS_5 = \033[38;2;63;0;191m
LINE_COLORS_6 = \033[38;2;0;0;255m
END			  = \033[0m

################################################################################
#                                  VISUALS                                     #
################################################################################

NAME_LINE_1 = .__          __  .__                            .__        __   			\n
NAME_LINE_2 = |  | _____ _/  |_|__| ____     ______ __________|__|______/  |_ 			\n
NAME_LINE_3 = |  | \__  \\    __\  |/    \   /  ___// ___\_ __ \  \____ \   __\			\n
NAME_LINE_4 = |  |__/ __ \|  | |  |   |  \  \___  \\  \___|  |\/  |  |_> >  |  			\n
NAME_LINE_5 = |____(____  /__| |__|___|  / /____  >\___  >__| |__|   __/|__|  			\n
NAME_LINE_6 =           \/             \/       \/     \/        |__|         			\n


PRINT_NAME = printf "\n$(LINE_COLORS_1) %4s $(NAME_LINE_1)$(LINE_COLORS_2) %4s $(NAME_LINE_2)$(LINE_COLORS_3) %4s $(NAME_LINE_3)$(LINE_COLORS_4) %4s $(NAME_LINE_4)$(LINE_COLORS_5) %4s $(NAME_LINE_5)$(LINE_COLORS_6) %14s $(NAME_LINE_6)$(END)\n"




SRCS_DIR	= omnia/src/

SRC_FILES	= $(SRCS_DIR)main.cpp 

INCLUDES	=	-Iinc

CXX			= @c++
CXXFLAGS 	= -g3 -Wall -Wextra -Werror -std=c++98 $(INCLUDES)


OBJS_DIR	= .objects
OBJS 		= $(SRC_FILES:%.cpp=$(OBJS_DIR)/%.o)

NAME 		= latin-script

all : $(NAME)

$(NAME) : $(OBJS_DIR) $(OBJS) Makefile
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	
$(OBJS_DIR) :
	@$(PRINT_NAME)
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/$(SRCS_DIR)
	@sleep 0.1
	@printf "$(LINE_COLORS_6)%15s Compilation of $(NAME) terminated $(END)$(LINE_COLORS_1)\
	$(BLINK)[$(LINE_COLORS_6)$(BLINK)success$(BLINK)$(LINE_COLORS_1)]$(END)\n\n"

$(OBJS) : $(OBJS_DIR)/%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean :
	@rm -rf $(OBJS_DIR)

fclean : clean
	@rm -rf $(NAME)
	@printf "\n$(LINE_COLORS_6)%20s Removing $(NAME)$(END)\n\n"

re : fclean all

.PHONY: all clean fclean re

