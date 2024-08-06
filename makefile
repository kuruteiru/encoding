clean:
	rm $(wildcard *.o) $(wildcard *.exe) encoding
	@echo "removed .o and .exe files"

build: main.c raygui/raygui.c huffman/huffman.c shannon-fano/shannon_fano.c
	gcc $^ -o build/encoding -I. -I/usr/local/include -L/usr/local/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	@echo "$^ compiled into executable" 

build.exe: main.c raygui/raygui.c huffman/huffman.c shannon-fano/shannon_fano.c
	gcc $^ -o build/encoding.exe -I. -I/usr/local/include -L/usr/local/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	@echo "$^ compiled into executable" 

huffman: main.c huffman/huffman.c
	gcc $^ -o build/encoding
	@echo "$^ compiled into $@"

main: main.c huffman/huffman.c shannon-fano/shannon_fano.c
	gcc $^ -o build/encoding
	@echo "$^ compiled into $@"
