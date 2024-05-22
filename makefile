clean:
	rm $(wildcard *.o) $(wildcard *.exe)
	@echo "removed .o and .exe files"

huffman: main.c huffman/huffman.c
	gcc $^ -o $@
	@echo "$^ compiled into $@"