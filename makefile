%: %.cpp
	g++ -o $@ $< -std=c++17 -DLOCAL -Wall -Wextra -Wconversion -Wshadow -Wno-sign-conversion -D_GLIBCXX_DEBUG -fno-sanitize-recover=undefined -fsanitize=undefined -DPRAYFORSOLVE -fsanitize=address
