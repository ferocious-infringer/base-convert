objects = main.o input.o base.o
output = base-convert

ifeq ($(OS),Windows_NT)
	output := $(output).exe
endif

$(output): $(objects)
	gcc -o $(output) $(objects)

$(objects): %.o: %.c %.h
	gcc -c $<

.PHONY: clean
clean:
	rm -f $(objects) $(output)
# use -f to suppress nonexistent files.
