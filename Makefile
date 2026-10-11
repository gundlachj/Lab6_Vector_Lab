CC=gcc
CCFLAGS=-c -Wall
LDFLAGS=

SOURCES=main.c vect.c
OBJECTS=$(SOURCES:.c=.o)

BIN=./bin
EXEC=exec

all: $(EXEC)

$(EXEC): $(OBJECTS) | $(BIN)
	$(CC) $(addprefix $(BIN)/, $(OBJECTS)) $(LDFLAGS) -o $(BIN)/$@

.c.o:
	@mkdir -p $(BIN)
	$(CC) $(CCFLAGS) $< -o $(BIN)/$@
	$(CC) -MM $< > $(BIN)/$*.d

$(BIN):
	@mkdir -p $@

clean:
	rm -rf $(BIN)

test: clean | $(EXEC)
	@echo "-------------"
	@$(BIN)/$(EXEC)
