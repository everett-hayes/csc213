CC := clang
CFLAGS := -g -Wall -Werror

all: ngram

clean:
	@echo "Removing build output"
	@rm -f ngram ngram.zip

ngram: ngram.c
	$(CC) $(CFLAGS) -o ngram ngram.c

zip:
	@echo "Generating ngram.zip file to submit to Gradescope..."
	@zip -q -r ngram.zip . -x .git/\* .vscode/\* .clang-format .gitignore ngram
	@echo "Done. Please upload ngram.zip to Gradescope."

.PHONY: all clean zip
