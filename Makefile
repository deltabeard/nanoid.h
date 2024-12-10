CFLAGS:=-O2 -g3 -Wall -Wextra -fanalyzer -fsanitize=undefined -fsanitize-trap
ifeq ($(OS),Windows_NT)
	LDLIBS:=-lBcrypt
endif
all: nanoidgen
