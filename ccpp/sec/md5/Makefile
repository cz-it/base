TEST_APP=md5
CFLAGS=-g -Wall


.DEFAULT : all

all: $(TEST_APP)

md5_depend= test_md5.c  md5.c cz_md5.c
md5_objs= $(patsubst %.c,%.o,$(md5_depend))

%.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS)

md5:$(md5_objs)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY : clean
clean:
	-rm *.o  -rf
	-rm $(TEST_APP)
