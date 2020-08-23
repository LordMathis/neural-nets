
build_dir:
	mkdir -p ./build

test: build_dir
	gcc -g ./test/*.c ./lib/*.c -o ./build/test -lm

xor: build_dir
	gcc -g ./examples/xor.c ./lib/*.c -o ./build/xor -lm

clean:
	rm -r ./build