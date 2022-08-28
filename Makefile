CC = avr-gcc

.PHONY: clean example
.SILENT: clean

all: example

clean:
	make -C example clean
	# find . -name "*.o" | xargs rm -f

example:
	make -C $@
