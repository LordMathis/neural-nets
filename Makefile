
build_dir:
	mkdir -p ./build

test: build_dir
	gcc -g ./test/*.c ./lib/*.c -o ./build/test -lm

clean:
	rm -r ./build