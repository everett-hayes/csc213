CC := clang
CFLAGS := -g -Wall -Werror

all: queue

clean:
	@echo "Removing build output"
	@rm -f queue queue.zip

queue: queue.c
	$(CC) $(CFLAGS) -o queue queue.c

zip:
	@echo "Generating queue.zip file to submit to Gradescope..."
	@zip -q -r queue.zip . -x .git/\* .vscode/\* .clang-format .gitignore queue
	@echo "Done. Please upload queue.zip to Gradescope."

.PHONY: all clean zip
