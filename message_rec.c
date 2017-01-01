#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#define MSGSZ     128

/*
 * Declare the message structure.
 */

typedef struct msgbuf {
    long mtype;     // The message type, represented in a positive number. This must be a positive number! 
    char mtext[MSGSZ];
} message_buf;

int main()
{
    int msqid;
    key_t key;
    message_buf rbuf;

    /*
     * Get the message queue id for the
     * "name" 1234, which was created by
     * the server.
     */
    key = 1234;
   //    IPC_CREAT | 0666 for a server (i.e., creating and granting read and write access to the server)
   //    0666 for any client (i.e., granting read and write access to the client)
    if ((msqid = msgget(key, 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    /*
     * Receive an answer of message type 1. Keep pace with message_send.c
     */
//4th arg: msgtyp >0：接收类型等于msgtyp的第一个消息
//5th arg: msgflg - 0: 阻塞式接收消息，没有该类型的消息msgrcv函数一直阻塞等待
    if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }

    /*
     * Print the answer.
     */
    printf("%s\n", rbuf.mtext);
    exit(0);
}
