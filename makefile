# makefile to build scanner and parser(assignment 3) for 2007a7ps125p , 2007a7ps110p
# --macros

OBJECTS = main.o util.o scan.o parse.o ast.o symtab.o cgen.o

# --targets

exe: $(OBJECTS)
	gcc -o exe $(OBJECTS) 

main.o: main.c
	gcc -g -I. -c main.c

util.o: util.c
	gcc -g -I. -c util.c

scan.o: scan.c
	gcc -g -I. -c scan.c

parse.o: parse.c
	gcc -g -I. -c parse.c

ast.o: ast.c
	gcc -g -I. -c ast.c

symtab.o: symtab.c
	gcc -g -I. -c symtab.c

cgen.o: cgen.c
	gcc -g -I. -c cgen.c

clean:
	rm -f exe $(OBJECTS)

