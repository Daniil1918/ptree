CC=gcc

all: ptree

ptree:
	$(CC) -o ptree ptree.c utils.c

clean:
	rm -rf ptree
