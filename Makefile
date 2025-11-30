.PHONY: build

clean:
	rm -rf build

build:
	cmake -B build -S . -G Ninja -DBUILD_DOCS=OFF -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF
	cmake --build build

test:
	ctest --test-dir build/tests
