#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <fcntl.h>

#define MQKEY 0X1234
#define ID1 101
#define ID2 201

typedef struct msg {
    long id;
    char fifo_name[256];
    char file_name[256];
} msg_t;

int main() {
    int mqid, ret, fifo_fd, output_fd;
    msg_t msg;
    char buffer[1024];

    // Create message queue
    mqid = msgget(MQKEY, IPC_CREAT | 0600);
    if (mqid < 0) {
        perror("msgget fail");
        _exit(1);
    }

    // Fill in message details
    msg.id = ID1;
    printf("Enter FIFO name: ");
    scanf("%s", msg.fifo_name);
    printf("Enter file name: ");
    scanf("%s", msg.file_name);

    // Send message to server
    ret = msgsnd(mqid, &msg, sizeof(msg) - sizeof(long), 0);
    if (ret < 0) {
        perror("msgsnd fail");
        _exit(1);
    }

    // Open FIFO for reading
    fifo_fd = open(msg.fifo_name, O_RDONLY);
    if (fifo_fd < 0) {
        perror("open fifo fail");
        _exit(1);
    }

    // Open output file for writing
    output_fd = open("received_file", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (output_fd < 0) {
        perror("open output file fail");
        _exit(1);
    }

    // Read from FIFO and write to output file
    ssize_t bytes_read;
    while ((bytes_read = read(fifo_fd, buffer, sizeof(buffer))) > 0) {
        if (write(output_fd, buffer, bytes_read) != bytes_read) {
            perror("write to output file fail");
            _exit(1);
        }
    }

    // Close file descriptors
    close(fifo_fd);
    close(output_fd);

    return 0;
}

