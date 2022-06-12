/** 
 * Create a C program that connects to this server and receives the serialized data from the server.
 * Your program should satisfy the following conditions.
 *      1. The program connects to port 8080 TCP of the server on any interface
 *      2. The program received the entire chunk of data from the server.
 *      3. The program deserializes the inbound data
 *      4. The program prints the data to screen
 * The structure is provided and the data is ordered the same. 
 * Hint:
 *      Refer to ex73.c for assistance on deserializing the data.
 * @file ex74.c
*/

#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <string.h>

#define PORT    "8080"
#define BACKLOG 10

typedef struct {
    char name[100];
    short age;
    char grade;
    char schoolName[100];

} StudentInfo;


void *get_in_addr(struct sockaddr *sa){
   if (sa->sa_family == AF_INET) {
       return &(((struct sockaddr_in*)sa)->sin_addr);
   }
   return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


char cBuffer[300] = {   0x54,0x61,0x70,0x69,0x6f,0x63,0x61,0x00,    // 8
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 16
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 24
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 32
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 40
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 48
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 56
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 64
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 72
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 80
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 88
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 96
                        0x00,0x00,0x00,0x00,0x00,0x11,0x0b,0x48,    // 104
                        0x61,0x63,0x6b,0x65,0x72,0x20,0x55,0x6e,    // 112
                        0x69,0x76,0x65,0x72,0x73,0x69,0x74,0x79,    // 120
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 128
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 136
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 144
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 152
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 160
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 168
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 176
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 184
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 192
                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 200
                        0x00,0x00,0x00  };                          // 203

int main(int argc, char **argv){
    struct addrinfo *servInfo;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family     = AF_UNSPEC;
    hints.ai_socktype   = SOCK_STREAM;
    hints.ai_flags      = AI_PASSIVE;

    int errCode = getaddrinfo(NULL, PORT, &hints, &servInfo);
    if(errCode != 0){
        fprintf(stderr,
                "Error: GetAddrinfo -> %s\n",
                gai_strerror(errCode));
        return -1;
    }

    struct addrinfo *pIter;
    int socketFileDescriptor;
    for(pIter = servInfo; pIter != NULL; pIter = pIter->ai_next){
        socketFileDescriptor = socket(	pIter->ai_family,
                                        pIter->ai_socktype,
                                        pIter->ai_protocol);
        if(socketFileDescriptor == -1){
            fprintf(stderr,
                    "Error: Socket() -> %d\n",
                    socketFileDescriptor);
            continue;
        }

        errCode = bind(	socketFileDescriptor,
                        pIter->ai_addr,
                        pIter->ai_addrlen);
        if(errCode == -1){
            fprintf(stderr,
                    "Error: Connect() -> %d\n",
                    errCode);
            close(socketFileDescriptor);
            continue;
        }
        break;
    }
    if(pIter == NULL){
        fprintf(stderr,
                "Error: Bind() failed.");
        return -2;
    }

    errCode = listen(socketFileDescriptor, BACKLOG);
    if(errCode == -1){
        fprintf(stderr,
                "Error: Listen() -> %d\n",
                errCode);
        close(socketFileDescriptor);
        return -3;
    }

    freeaddrinfo(servInfo);

    int totalTransmitted = 0;
    while(1){
        int clientSocketFildDescriptor;
        struct sockaddr_storage clientAddr;
        socklen_t sin_size = sizeof(clientAddr);

        clientSocketFildDescriptor = accept(socketFileDescriptor,
                (struct sockaddr*)&clientAddr,
                &sin_size);

        char hostString[INET6_ADDRSTRLEN] = {'\0'};
        inet_ntop(  clientAddr.ss_family,
                    get_in_addr((struct sockaddr*)&clientAddr),
                    hostString,
                    sizeof(hostString));
        printf("Server-> (Inbound Connection) : %s\n", hostString);

        int bytesTransmitted = 0;
        bytesTransmitted = send(clientSocketFildDescriptor,
                                cBuffer,
                                sizeof(cBuffer),
                                0);
        if(bytesTransmitted == -1){
            fprintf(stderr,
                "Error: Send() -> %d\n",
                bytesTransmitted);
            close(clientSocketFildDescriptor);
        }
        close(clientSocketFildDescriptor);
    }
    
    close(socketFileDescriptor);
    return 0;
}
