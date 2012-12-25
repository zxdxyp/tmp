all:
	gcc -Wall five_chess.c -o demo
	gcc -Wall five_chess2.c -o demo2
	gcc log.c -o log
	gcc replay.c -o replay 

clean:
	-rm *.o *.gz *.bak

run:
	./demo

p:
	mkfifo p1 p2

t1:
	rm log.txt
	cat p1 | ./demo pc | ./log > p2

t2:
	cat p2 | ./demo2 peo | ./log > p1

re:
	./replay log.txt
