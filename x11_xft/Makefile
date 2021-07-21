# Install
BIN = zahnrad

# Flags
CFLAGS += -std=c11 -pedantic -O2 -L/usr/local/lib 
CFLAGS += -I/usr/local/include -I/usr/local/include/freetype2
CFLAGS += ${shell pkg-config --cflags xft} -DNK_XLIB_USE_XFT
LDFLAGS += ${shell pkg-config --libs xft}

SRC = main.c 
OBJ = $(SRC:.c=.o)

$(BIN):
	@mkdir -p bin
	rm -f bin/$(BIN) $(OBJS)
	$(CC) $(SRC) $(CFLAGS)  -o bin/$(BIN) -lX11 -lXft -lm


	# $(CC) $(SRC) $(CFLAGS) -D_POSIX_C_SOURCE=200809L -o bin/$(BIN) -lX11 -lXft -lm
