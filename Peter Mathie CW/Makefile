
parser:
	flex FUNC.lex
	gcc -c lex.yy.c
	gcc -c tree.c
	gcc -c parser.c
	gcc -o parser lex.yy.o tree.o parser.o

ast-parser:
	flex FUNC.lex
	gcc -c lex.yy.c
	gcc -c tree.c
	gcc -c ast-parser.c
	gcc -o ast-parser lex.yy.o tree.o ast-parser.o

clean:
	rm -rf *.o lex.yy.c lexical parser astparser
