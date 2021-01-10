NAME = client

SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = inc/

DIRS	= $(notdir $(wildcard $(SRC_DIR)*))
FILES	= $(foreach dir, $(DIRS), $(basename $(wildcard $(SRC_DIR)$(dir)/*.c)))
SRC		= $(FILES:%=%.c)
OBJ		= $(SRC:src/%.c=$(OBJ_DIR)%.o)
INC_H	= $(wildcard $(INC_DIR)*.h)


CC		 = clang
GFLAGS		= -rdynamic `pkg-config --cflags --libs gtk+-3.0`\
			  -std=c11 -Wall -Wextra\
			  -Wno-unused-command-line-argument -Wno-unused-variable \
			  -Wno-unused-function -Wno-unused-parameter -g
IFLAGS	 = $(addprefix -I, $(INC_DIR))
COMPILE	 = $(CC) $(GFLAGS) $(IFLAGS)


MAKE_M	 = make -sf Makefile -C
MKDIR	 = mkdir -p
RM		 = /bin/rm -rf


all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@printf "Test3\n"
	@$(COMPILE) $(OBJ) -o $(NAME)
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@$(MKDIR) $@ $(foreach dir, $(DIRS), $@/$(dir))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_H)
	@$(COMPILE) -o $@ -c $<
	@printf "\r\33[2K$(NAME) \033[33;1mcompile \033[0m$(<:$(SRC_DIR)/%.c=%)"

clean:
	@$(RM) $(OBJ_DIR)
	@printf "obj in $(NAME)\t \033[31;1mdeleted\033[0m\n"

uninstall:
	@$(RM) $(OBJ_DIR) $(NAME)
	@printf "$(NAME)\t \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
