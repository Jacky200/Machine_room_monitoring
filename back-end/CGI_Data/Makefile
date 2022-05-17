SOURCE :=sour_data.c cJSON.c
OBJ :=get_data.o cJSON.o

TARGET :=get_data

CC :=gcc
CROSS_COMPILE :=
INCLUDE :=-I .
DEFINES :=
CFLAGS :=-g -Wall $(INCLUDE) $(INCLUDE)
LDFLAGS :=
OUTPUT := /home/jacky/www/cgi

all:$(TARGET)
$(TARGET):$(OBJ)
	$(CROSS_COMPILE)$(CC) -o $@ $^ $(LDFLAGS)
	cp $(TARGET) $(OUTPUT)
%.o:%.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -c -o $@ $^
.PHONY:clean
clean:
	rm *.o $(TARGET)