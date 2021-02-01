# Makefile para MAC0328 (2019).
# Codificação: UTF-8.
# Modifique à vontade!
########################################################################


STD = -std=c99

OP  = -Wall -Wextra -Wpedantic -Wshadow -Wno-unused-result -Wno-unused-function

## optimization
OPTM = -O0
# OPTM = -O2

# GDB = -g

# onde compilador deve procurar GRAPHlists.h, QUEUE.h, etc.
INC = -I./bib

LM = 
# LM = -lm
##  in case you use sqrt, sin, cos, etc.

# serão compilados junto com programa-cliente
BIB = \
bib/GRAPHlists.c \
bib/STACK.c \
bib/QUEUE.c \
bib/PQ.c \
bib/maxPQ.c \
bib/UF.c \
bib/MYTOOLS.c

VERBOSE = -v

.FORCE :

default : 
	@echo "Para compilar prog.c diga 'make prog'"
	@echo ""

% : %.c .FORCE
	@echo "-------"
	gcc $(STD) $(OP) $(OPTM) $(INC) $< $(BIB) -o $@ $(LM)
	@echo "-------"
	@echo ""

