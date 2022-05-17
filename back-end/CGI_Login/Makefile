SOURCE :=regist.c cgic.c sqlite3.c
OBJ :=regist.o cgic.o sqlite3.o

TARGET :=regist

CC :=gcc
CROSS_COMPILE :=
INCLUDE := -I .
DEFINES :=
CFLAGS :=-g -Wall $(INCLUDE) $(DEFINES)
LDFLAGS := -lpthread -ldl
OUTPUT := /home/jacky/www/cgi

all:$(TARGET)
$(TARGET):$(OBJ)
	$(CROSS_COMPILE)$(CC) -o $@ $^ $(LDFLAGS)
	cp $(TARGET) $(OUTPUT)
%.o:%.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -c -o $@ $^
.PHONY:clean
clean:
	rm -rf *.o $(TARGET)