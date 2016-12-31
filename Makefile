CC              =   gcc
CFLAGS          =   -g
RM              =   rm -f

default: all 

all: message_send message_rec

message_send: message_send.c
	$(CC) $(CFLAGS) -o message_send message_send.c

message_rec: message_rec.c
	$(CC) $(CFLAGS) -o message_rec message_rec.c

clean veryclean:
	$(RM) message_send message_rec
