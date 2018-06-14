all:	3600fs 3600mkfs

3600fs: 3600fs.c subdirs.c disk.c disk.h 3600fs.h 
	gcc 3600fs.c subdirs.c disk.c -std=gnu99 -lfuse -O0 -g -lm  -pedantic -Wextra -D_FILE_OFFSET_BITS=64 -DFUSE_USE_VERSION=26 -o $@

3600mkfs: 3600mkfs.c disk.c disk.h 3600fs.h
	gcc $< disk.c -std=gnu99 -O0 -g -lm -Wall -pedantic -Wextra -D_FILE_OFFSET_BITS=64 -DFUSE_USE_VERSION=26 -o $@

test: 3600fs 3600mkfs
	./3600mkfs 1000
	./3600fs -s -d ./temp

clean:	
	rm -f 3600fs 3600mkfs fs-log.txt log.txt

squeaky: clean
	rm -f MYDISK
