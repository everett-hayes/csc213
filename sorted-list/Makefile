CC := clang
CFLAGS := -g -Wall -Werror -fsanitize=address

all: sorted-list

clean:
	@echo "Removing build output"
	@rm -rf sorted-list.dSYM sorted-list sorted-list.zip

sorted-list: main.c sorted-list.c sorted-list.h
	$(CC) $(CFLAGS) -o sorted-list main.c sorted-list.c

zip:
	@echo "Generating sorted-list.zip file to submit to Gradescope..."
	@zip -q -r sorted-list.zip . -x .git/\* .vscode/\* .clang-format .gitignore sorted-list
	@echo "Done. Please upload sorted-list.zip to Gradescope."

.PHONY: all clean zip
