LINE_COLORS_1 = \033[38;2;255;0;0m
LINE_COLORS_2 = \033[38;2;226;0;28m
LINE_COLORS_3 = \033[38;2;198;0;56m
LINE_COLORS_4 = \033[38;2;170;0;85m
LINE_COLORS_5 = \033[38;2;141;0;113m
LINE_COLORS_6 = \033[38;2;113;0;141m
LINE_COLORS_7 = \033[38;2;85;0;170m
LINE_COLORS_8 = \033[38;2;56;0;198m
LINE_COLORS_9 = \033[38;2;28;0;226m
END			  = \033[0m

################################################################################
#                                  VISUALS                                     #
################################################################################

NAME_LINE_1 =  ▄█          ▄████████     ███      ▄█  ███▄▄▄▄           ▄████████  ▄████████    ▄████████  ▄█     ▄███████▄     ███     \n
NAME_LINE_2 = ███         ███    ███ ▀█████████▄ ███  ███▀▀▀██▄        ███    ███ ███    ███   ███    ███ ███    ███    ███ ▀█████████▄ \n
NAME_LINE_3 = ███         ███    ███    ▀███▀▀██ ███▌ ███   ███        ███    █▀  ███    █▀    ███    ███ ███▌   ███    ███    ▀███▀▀██ \n
NAME_LINE_4 = ███         ███    ███     ███   ▀ ███▌ ███   ███        ███        ███         ▄███▄▄▄▄██▀ ███▌   ███    ███     ███   ▀ \n
NAME_LINE_5 = ███       ▀███████████     ███     ███▌ ███   ███      ▀███████████ ███        ▀▀███▀▀▀▀▀   ███▌ ▀█████████▀      ███     \n
NAME_LINE_6 = ███         ███    ███     ███     ███  ███   ███               ███ ███    █▄  ▀███████████ ███    ███            ███     \n
NAME_LINE_7 = ███▌    ▄   ███    ███     ███     ███  ███   ███         ▄█    ███ ███    ███   ███    ███ ███    ███            ███     \n
NAME_LINE_8 = █████▄▄██   ███    █▀     ▄████▀   █▀    ▀█   █▀        ▄████████▀  ████████▀    ███    ███ █▀    ▄████▀         ▄████▀   \n
NAME_LINE_9 = ▀                                                                                ███    ███                               \n



PRINT_NAME = echo "\n$(LINE_COLORS_1)$(NAME_LINE_1)$(LINE_COLORS_2)$(NAME_LINE_2)$(LINE_COLORS_3)$(NAME_LINE_3)$(LINE_COLORS_4)$(NAME_LINE_4)$(LINE_COLORS_5)$(NAME_LINE_5)$(LINE_COLORS_6)$(NAME_LINE_6)$(LINE_COLORS_7)$(NAME_LINE_7)$(LINE_COLORS_8)$(NAME_LINE_8)$(LINE_COLORS_9)$(NAME_LINE_9)$(END)"




SRCS_DIR	= omnia/src/
CORE_DIR	= $(SRCS_DIR)core/
UTILS_DIR	= $(SRCS_DIR)utils/

SRC_FILES	= $(addprefix $(SRCS_DIR), main.cpp LatinScript.cpp) \
				$(addprefix $(UTILS_DIR), Utils.cpp) \
				$(addprefix $(CORE_DIR), Object.cpp Numerus.cpp Functio.cpp \
										ScriptRunner.cpp Filum.cpp Duplus.cpp)

INCLUDES	=	-Iomnia/inc \
					-Iomnia/inc/core \
					-Iomnia/inc/utils

CXX			= @c++
CXXFLAGS 	= -g3 -Wall -Wextra -Werror $(INCLUDES) #-fsanitize=address 


OBJS_DIR	= .objects
OBJS 		= $(SRC_FILES:%.cpp=$(OBJS_DIR)/%.o)

NAME 		= latin-script

all : $(NAME)

$(NAME) : $(OBJS_DIR) $(OBJS) Makefile
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@printf "$(LINE_COLORS_3)%15s Compilation of $(NAME) terminated $(END)$(LINE_COLORS_1)\
	$(BLINK)[$(LINE_COLORS_6)$(BLINK)success$(BLINK)$(LINE_COLORS_1)]$(END)\n\n"
	
$(OBJS_DIR) :
	@$(PRINT_NAME)
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/$(SRCS_DIR)
	@mkdir -p $(OBJS_DIR)/$(CORE_DIR)
	@mkdir -p $(OBJS_DIR)/$(UTILS_DIR)

$(OBJS) : $(OBJS_DIR)/%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJS_DIR)

fclean : clean
	@rm -rf $(NAME)
	@printf "\n$(LINE_COLORS_3)%20s Removing $(NAME)$(END)\n\n"

re : fclean all

.PHONY: all clean fclean re

