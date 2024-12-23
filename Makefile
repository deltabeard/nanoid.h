CFLAGS:=-O2 -g3 -Wall -Wextra -fanalyzer -fsanitize=undefined -fsanitize-trap
ifeq ($(OS),Windows_NT)
nanoidgen: LDLIBS:=-lBcrypt
endif

nanoidgen_win32: override CFLAGS += -fno-builtin -nostartfiles -mconsole

all: nanoidgen nanoidgen_win32
