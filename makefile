all: serv cli

serv: major2serv.c
	gcc -o serv major2serv.c

cli: major2cli.c
	gcc -o cli major2cli.c

.PHONY:
	clean

clean:
	rm cli serv
