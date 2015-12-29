all:
	byacc -dvt hw2.y
	flex hw2.l
	gcc lex.yy.c y.tab.c -lfl
	./a.out < testfile.c

clean:
	rm -f lex.yy.c y.tab.c a.out
