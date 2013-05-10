#TIME = `date +%x`
TIME = $(shell date '+%H-%M')

all:
	gcc fivechess.c -o demo
	gcc log.c -o log
	gcc replay.c -o replay

rmlog:
	-rm *.log
	-rm *.log.html

t:
	echo $(TIME)
	-rm m.log m.log.html
	ln -s $(TIME).log m.log	
	ln -s $(TIME).log.html m.log.html	
	./demo | ./log $(TIME).log 
	cat match0.html m.log.html match1.html > match-record.html

http:
	python -m SimpleHTTPServer
