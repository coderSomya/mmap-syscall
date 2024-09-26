EXE=01-allocating-memory.exe 02-reading-files.exe 03-ipc.exe

.PHONY: all
all: $(EXE)

%.exe: %.c
	gcc -Wall -o $@ $<

.PHONY: clean
clean:
	rm -rfv $(EXE)
