.PHONY:	clean run

include ../cpu.mk

TARGETS=receiver sender 
UTILS=util.o 

all: $(TARGETS)

$(UTILS): %.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

%.o: %.c util.h
	$(CC) $(CFLAGS)  -c $< 

$(TARGETS): %:%.o util.o
	$(CC) $(CFLAGS) $^ -o $@

run_sender: sender 
	taskset -c $(SENDER_CPU) ./sender

run_receiver: receiver
	taskset -c $(RECEIVER_CPU) ./receiver

run: $(TARGETS)
	@taskset -c $(RECEIVER_CPU) ./receiver & \
	taskset -c $(SENDER_CPU) ./sender

loop:
	@for i in $(shell seq 1 5); do \
        taskset -c $(RECIEVER_CPU) ./receiver & \
        taskset -c $(SENDER_CPU) ./sender;
	 done

clean:
	$(RM) *.o $(HELPERS) $(TARGETS) 
