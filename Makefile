
build_dir:
	mkdir -p ./build

test: build_dir
	gcc -DUNIT_TEST -g ./test/*.c ./lib/*.c -o ./build/test -lm

xor: build_dir
	gcc -g ./examples/xor.c ./lib/*.c -o ./build/xor -lm

mnist: build_dir
	gcc -g ./examples/mnist.c ./lib/*.c -o ./build/mnist -lm

clean:
	rm -r ./build