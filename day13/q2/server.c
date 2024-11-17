#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MQKEY 0X1234
#define ID1 101
#define ID2 201

typedef struct msg {
    long id;
    char fifo_name[256];
    char file_name[256];
} msg_t;

int main() {
    int mqid, ret, fifo_fd, file_fd;
    char buffer[1024];
    msg_t msg;
    
    // Create message queue
    mqid = msgget(MQKEY, IPC_CREAT | 0600);
    if (mqid < 0) {
        perror("msgget fail");
        _exit(1);
    }

    // Receive message from client
    ret = msgrcv(mqid, &msg, sizeof(msg) - sizeof(long), ID1, 0);
    if (ret < 0) {
        perror("msgrcv fail");
        _exit(1);
    }
    printf("Received FIFO name: %s, File name: %s\n", msg.fifo_name, msg.file_name);

    // Open the file to read
    file_fd = open(msg.file_name, O_RDONLY);
    if (file_fd < 0) {
        perror("open file fail");
        _exit(1);
    }

    // Create and open FIFO
    if (mkfifo(msg.fifo_name, 0666) == -1) {
        perror("mkfifo fail");
        _exit(1);
    }
    fifo_fd = open(msg.fifo_name, O_WRONLY);
    if (fifo_fd < 0) {
        perror("open fifo fail");
        _exit(1);
    }

    // Read from file and write to FIFO
    ssize_t bytes_read;
    while ((bytes_read = read(file_fd, buffer, sizeof(buffer))) > 0) {
        if (write(fifo_fd, buffer, bytes_read) != bytes_read) {
            perror("write to fifo fail");
            _exit(1);
        }
    }

    // Close file descriptors
    close(file_fd);
    close(fifo_fd);

    // Remove message queue
    msgctl(mqid, IPC_RMID, NULL);

    return 0;
}

