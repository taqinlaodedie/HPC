# -------------- #
# -- Makefile -- #
# -------------- #

# Copyright (c) 2000-2007 Lionel Lacassagne
# with a little help of Stephane Piskorski and Joel Falcou

# -- Lile list ----------
FILE = main.c test_mouvement.c test_mouvement_SIMD.c test_morpho.c test_morpho_SIMD.c morpho.c morpho_SIMD.c mouvement.c mouvement_SIMD.c nrutil.c vnrutil.c mutil.c myutils.c

# -- Paths ----------
SRC_PATH = src
OBJ_PATH = obj
INC_PATH = include

# -- OS ----------
#OS = MACH_OSX

# -- Config ----------
# if CONFIG = CLI  (Command Line Interface, no Apple Framework)
CONFIG = CLI

# -- Macros ----------
CC = gcc
AR = ar -rc

# -- Flags ----------
C_DEBUG_FLAGS = -O0
C_CC_FLAGS = -std=c99 -DNOALIAS -DALIGNED -DmySSE -DTIMER_POSIX6 -fopenmp
C_OPTIMISATION_FLAGS = -O3 -fstrict-aliasing
C_ARCH_FLAGS = -msse4.2

C_OS_FLAGS =
C_CONFIG_FLAGS = -D$(CONFIG)
C_INC_FLAGS = -I$(INC_PATH)

CFLAGS =  $(C_CC_FLAGS) $(C_DEBUG_FLAGS)        $(C_ARCH_FLAGS) $(C_OS_FLAGS) $(C_CONFIG_FLAGS) $(C_INC_FLAGS) $(LIB_INC_PATH)
CFLAGS = $(C_CC_FLAGS) $(C_OPTIMISATION_FLAGS) $(C_ARCH_FLAGS) $(C_OS_FLAGS) $(C_CONFIG_FLAGS) $(C_INC_FLAGS) $(LIB_INC_PATH)
LDFLAGS = $(C_CC_FLAGS) $(C_OPTIMISATION_FLAGS) $(C_ARCH_FLAGS) $(C_OS_FLAGS) $(C_CONFIG_FLAGS) $(C_INC_FLAGS) $(LIB_LIB_PATH)

# -- Final product ----------
PRODUCT   = main

# -- src and obj List ----------
SRC = $(addprefix ${SRC_PATH}/, $(FILE))
OBJ = $(addprefix ${OBJ_PATH}/, $(addsuffix .o, $(basename $(FILE))))

# -- Base rules ----------
$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

#-----Main rule ----------
$(PRODUCT): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(OPTFLAGS) $(CFG) $(INC) $(LIB) -lm

# -- Other stuff ----------
depend:
	makedepend $(CFLAGS) -Y $(SRC)

clean:
	rm -f $(OBJ)
	rm -f ${PRODUCT}
	rm -f test_img/mouvement/*.pgm test_img/morpho/*.pgm output/*.pgm

tar:
	tar -cvf deriche_SSE.tar Makefile src include
	gzip -9 deriche_SSE.tar
