NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror

EXTERNAL_LIBS = -pthread

SAFE_MKDIR = mkdir -p

COPY = cp -p

REMOVE = rm -rf

OBJECTS_PATH = ./objects
SOURCES_PATH = ./sources
INCLUDES_PATH = ./includes

ARCHIVES_PATH = ./archives

HEADER_FILE = philo.h
HEADER = $(addprefix $(INCLUDES_PATH)/,$(HEADER_FILE))

SOURCE_FILES =	main.c \
				init.c \
				threads.c \
				actions.c \
				times.c \
				helpers.c

SOURCES = $(addprefix $(SOURCES_PATH)/,$(SOURCE_FILES))

OBJECTS = $(addprefix $(OBJECTS_PATH)/,$(subst .c,.o,$(SOURCE_FILES)))

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
	@$(CC) $(CFLAGS) -w -g $(OBJECTS) -o $(NAME) -L $(ARCHIVES_PATH) -I $(INCLUDES_PATH) $(EXTERNAL_LIBS)

$(OBJECTS_PATH)/%.o: $(SOURCES_PATH)/%.c $(HEADER)
	@$(SAFE_MKDIR) $(OBJECTS_PATH)
	@$(CC) $(CFLAGS) -g -I $(INCLUDES_PATH) -o $@ -c $< $(EXTERNAL_LIBS)

re:	fclean all

archives_clean:
	$(REMOVE) $(ARCHIVES_PATH)

clean:
	$(REMOVE) $(OBJECTS_PATH)

fclean: clean archives_clean
	$(REMOVE) $(NAME)

.PHONY: all run re fclean clean archives_clean
