#Global uses of variables
SRC = src/main.c
OBJ = $(SRC:.c=.o)
#/////////////////////////////////////////////////////////////////////////////////
#Here goes the Linux commad section
LINUXCC = gcc
#Find the flags for gcc these below are clang flags
LFLAGS = -Wall -Wextra -std=gnu23 -g -Iheaders
LINUXDELCMD = rm
# Source and object files
LINUXDEL =  ./src/bubble.o  ./src/main.o
LINUXOBJ1 = ./main
# Target executable
LINUXTARGET = mainl
LINUXTARGET1 = gol
LINUXCLEAN = cleanl
#Build
$(LINUXTARGET): $(OBJ)
	$(LINUXCC) $(LFLAGS) -o $@ $(OBJ)

$(LINUXTARGET1): $(LINUXOBJ1)
	$(LINUXOBJ1)

$(LINUXCLEAN):
	$(LINUXDELCMD) $(LINUXDEL)


#//////////////////////////////////////////////////////////////////////////////////
#Here goes windows command section


WINDOWSCC = clang
SIMPLEFLAGS = -Wall -I../raylib/include
RAYLIBFLAGS = -Wall -I../raylib/include -L../raylib/lib -lraylib -lmsvcrt  -lgdi32 -lwinmm 
WCFLAGS = -Wall -Wextra -std=gnu2y -g -Iheaders $(RAYLIBFLAGS)
WINDOWSDELCMD = del
# Source and object files
WINDOWSDEL =  .\src\main.o
WINDOWSOBJ1 = ./mainw.exe
# Target executable
WINDOWSTARGET = mainw
WINDOWSTARGET1 = gow
WINDOWSCLEAN = cleanw
#
#build
$(WINDOWSTARGET): $(OBJ)
	$(WINDOWSCC) $(RAYLIBFLAGS) -o $@ $(OBJ)
%.o: %.c
	$(WINDOWSCC) -c $(RAYLIBFLAGS) $< -o $@

$(WINDOWSTARGET1): $(WINDOWSOBJ1)
	$(WINDOWSOBJ1)

$(WINDOWSCLEAN):
	$(WINDOWSDELCMD) $(WINDOWSDEL)


