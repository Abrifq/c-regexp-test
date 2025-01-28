CFLAGS=-ggdb3 -O0 -Wall -Werror -Wextra -D_POSIX_C_SOURCE=200112L -fsanitize=address -fsanitize=undefined -fsanitize=leak -fanalyzer -pedantic -pedantic-errors
all: out/main out/example

out/% : %.c | out/
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@

out/ :
	-mkdir -p $@

clean:
	-rm -r out/*