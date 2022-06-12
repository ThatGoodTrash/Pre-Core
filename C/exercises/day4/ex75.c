/** 
 * Fix this C program so that it connects to the link specified and downloads the image from the webpage.
 * Once downloaded, write that data to a file and open it to see the contents and verify you succeeded.
 * ***** Note ***** Note ***** Note ***** Note ***** Note ***** Note *****
 * Look into opening and writing files. You've already gained experience with 'write', and 
 * the data you're downloading is binary, so your way forward should be preserving what you downloaded.
 * Also, remember that you're receiving the ENTIRE response all at once. You'll need to
 * use some string manipulation to split the response header from the image data itself.
 * Finally, if everything looks fine and you're receiving data yet everything is
 * still not working, then look to your buffer size. Either increase it, or loop
 * recv until you receive 0 bytes and append the data at the end of a file. A
 * good place to look is at the 'Content-Length' header passed to you in the response.
 * Perhaps a bit of dynamic memory is in store?
 * ***********************************************************************
 * Good luck!
 * @file ex75.c
*/

#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <string.h>

#define PORT "http"
#define LINK "imgs.xkcd.com"


void *get_in_addr(struct sockaddr *sa){
   if (sa->sa_family == AF_INET) {
       return &(((struct sockaddr_in*)sa)->sin_addr);
   }
   return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char **argv){
    struct addrinfo *servInfo;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family     = AF_UNSPEC;
    hints.ai_socktype   = SOCK_STREAM;

    int errCode = getaddrinfo(LINK, PORT, &hints, &servInfo);
    if(errCode != 0){
        fprintf(stderr,
                "Error: GetAddrinfo -> %s\n",
                gai_strerror(errCode));
        return -1;
    }

    struct addrinfo* pIter;
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

        errCode = connect(	socketFileDescriptor,
                            pIter->ai_addr,
                            pIter->ai_addrlen);
        if(errCode == -1){
            fprintf(stderr, "Error: Connect() -> %d\n", errCode);
            close(socketFileDescriptor);
            continue;
        }
        break;
    }
    if(pIter == NULL){
        fprintf(stderr, "Error: Connect() failed.");
        return -2;
    }
    char hostString[INET6_ADDRSTRLEN] = {'\0'};
    inet_ntop(	pIter->ai_family,
                pIter->ai_addr->sa_data,
                hostString,
                sizeof(hostString));
    printf("Connecting to %s\n", hostString);
    freeaddrinfo(servInfo);

    int totalTransmitted = 0;
    int bytesTransmitted = 0;
    char* REQ = "GET /comics/real_programmers.png HTTP/1.1\r\nHost: imgs.xkcd.com\r\n\r\n";
    while(totalTransmitted < strlen(REQ)){
        bytesTransmitted = write(socketFileDescriptor,
                                REQ+totalTransmitted,
                                strlen(REQ)-totalTransmitted);
        if(bytesTransmitted == -1){
            fprintf(stderr,
                    "Error: Write() -> %d\n",
                    bytesTransmitted);
            return -3;
        }
        totalTransmitted += bytesTransmitted;
    }
    char dataBuffer[1024] = {'\0'};
    bytesTransmitted = recv(socketFileDescriptor,
                            dataBuffer,
                            1024, 
                            0);
    if(bytesTransmitted == -1){
        fprintf(stderr,
                "Error: Recv() -> %d.\n", 
                bytesTransmitted);
        return -3;
    }
    dataBuffer[1023] = '\0';
    printf("Received Data\n----------\n%s\n-----------\n",
            dataBuffer);

    close(socketFileDescriptor);
    return 0;
}
