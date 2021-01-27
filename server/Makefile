NAME = uchat_server


SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = inc/
MEDIA_DIR = media/


SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ		= $(SRC:src/%.c=$(OBJ_DIR)%.o)
INC_H	= $(wildcard $(INC_DIR)*.h)


LIB_DIR	 = .
LIB_LIST = libmx
LIB_DIRS = $(foreach libdirs, $(LIB_LIST), $(LIB_DIR)/$(libdirs)/)
LIB_BIN	 = $(join $(LIB_DIRS), $(addsuffix .a, $(LIB_LIST)))
LIB_INC	 = $(addsuffix $(INC_DIR), $(LIB_DIRS))


CC		 = clang
GFLAGS		= -std=c11 -Wall -Wextra -Werror -Wpedantic \
			  -Wno-unused-command-line-argument -Wno-unused-variable \
			  -Wno-unused-function -Wno-unused-parameter -g \
			  -lsqlite3 -lpthread
IFLAGS	 = $(addprefix -I, $(LIB_INC) $(INC_DIR))
COMPILE	 = $(CC) $(GFLAGS) $(IFLAGS) $(LIB_BIN)


MAKE_M	 = make -sf Makefile -C
MKDIR	 = mkdir -p
RM	 = /bin/rm -rf


all: $(NAME)

$(NAME): $(LIB_LIST) $(OBJ_DIR) $(OBJ)
	@$(COMPILE) $(OBJ) $(LIB_BIN) -o $(NAME)
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(LIB_BIN): $(LIB_LIST)

$(LIB_LIST): $(LIB_DIRS)
	@$(MAKE_M) $(LIB_DIR)/$@

$(OBJ_DIR):
	@$(MKDIR) $@ $(foreach dir, $(DIRS), $@/$(dir))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_H) $(LIB_BIN)
	@$(COMPILE) -o $@ -c $<
	@printf "\r\33[2K$(NAME) \033[33;1mcompile \033[0m$(<:$(SRC_DIR)/%.c=%)"

clean:
	@$(MAKE_M) $(LIB_DIR)/$(LIB_LIST) $@
	@$(RM) $(OBJ_DIR)
	@printf "obj in $(NAME)\t \033[31;1mdeleted\033[0m\n"

uninstall:
	@$(MAKE_M) $(LIB_DIR)/$(LIB_LIST) $@
	@$(RM) $(OBJ_DIR) $(NAME)
	@$(RM) $(MEDIA_DIR)
	@printf "$(NAME)\t \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all

.PHONY: all clean uninstall reinstall $(LIB_LIST)
