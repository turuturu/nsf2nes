CL65	= cl65
LD65	= ld65

#-------------------------------------------------------------------------------
CSOURCES = ${SRC_FILE}

ASMSOURCES =	${ASM_FILE}

OBJECTS	=	$(CSOURCES:.c=.o) $(ASMSOURCES:.asm=.o)

LIBRARIES =	
#-------------------------------------------------------------------------------
all :	$(OBJECTS) $(LIBRARIES)
	LD65 -o ${OUTPUT_FILE} --config ${CFG_FILE} --obj $(OBJECTS) --lib nes.lib

.SUFFIXES : .asm .o

.c.o :
	CL65 -t none -o $*.o -c -O $*.c

.asm.o :
	CL65 -t none -o $*.o -c $*.asm

clean :
	rm *.nes
	rm *.o
