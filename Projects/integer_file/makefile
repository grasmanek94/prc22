comma:= ,
empty:=
space:= $(empty) $(empty)

CYGWIN_BASE=/cygdrive/$(subst \,/,$(subst :,$(empty),$(CYGWIN64)))
PRC22LIBS=$(CYGWIN_BASE)/prc22libs

mkfile_path := $(subst $(space),$(empty),$(abspath $(lastword $(MAKEFILE_LIST))))
project_name := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

#actual program
RESOURCE_CHECK_FOLDER=$(PRC22LIBS)/ResourceDetector

INC_DIRS=-I$(RESOURCE_CHECK_FOLDER)

CFLAGS = -Wall -Werror -pedantic -O2 -std=c99 -g

TEST_MAIN_SRC = $(project_name)_test.c

SRC=$(filter-out $(TEST_MAIN_SRC), $(wildcard *.c) $(wildcard */*.c))

#testing
UNITY_FOLDER=$(PRC22LIBS)/Unity
TEST=$(project_name)_test
TEST_INC_DIRS=$(INC_DIRS) -I$(UNITY_FOLDER)
TEST_CFLAGS = $(CFLAGS) -DTEST
MAIN_SRC=main.c

TEST_SRC=$(filter-out $(MAIN_SRC), $(SRC)) $(UNITY_FOLDER)/unity.c $(TEST_MAIN_SRC)

all: clean $(project_name) $(TEST)

$(project_name): $(SRC)
	gcc $(INC_DIRS) -o $@ $^ $(CFLAGS)

$(TEST): $(TEST_SRC)
	gcc $(TEST_INC_DIRS) -o $@ $^ $(TEST_CFLAGS)

clean:
	rm -f $(project_name) $(TEST)

test: $(TEST)
	@./$(TEST)
