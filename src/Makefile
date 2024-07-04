# Running in Windows assumes that MinGW is installed and the path is set.

SRC := $(wildcard *.c)

OBJ := ${SRC:.c=.o}

ifeq ($(OS),Windows_NT)
    # Windows_NT on XP, 2000, 7, Vista, 10...
    detected_OS := Windows
	CC := gcc
else
    detected_OS := $(shell uname) # same as "uname -s"
	CC := gcc
endif

ifeq ($(detected_OS),Windows)
	TARGETDIR := ..\bin
	TARGET := $(TARGETDIR)/espresso.exe

	MKDIR_P := mkdir
	RM := del /Q
else
	MKDIR_P := mkdir -p
	TARGETDIR := ../bin
	TARGET := $(TARGETDIR)/espresso
	RM := rm -f -r
endif

all: prepare $(TARGET)

prepare: $(TARGETDIR)

$(TARGETDIR):
	mkdir $(TARGETDIR)

$(TARGET): $(OBJ)
	$(LINK.c) $(OBJ) -o $(TARGET)

clean:
	@- $(RM) $(TARGETDIR)
	@- $(RM) $(OBJ)

