/**
 * core.c contains all of the functionality for the core RoadRunner commands, checkin and sleep.
 * @file core.c
 */

#include <core.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Check in with the RoadRunner command post.
 * @return a Response structure
 */
Response *checkin_command()
{
    // struct response_struct checkin_resp;
    // checkin_resp.ret_code = 0;
    // strcpy(checkin_resp.msg, "roadrunner checkin");
    // checkin_resp.msg_len = checkin_resp.ret_code + strlen(checkin_resp.msg);


    int ret_code = 0;
    char checkin_resp[19] = "roadrunner checkin";
    //unsigned int message_length = ret_code + strlen(checkin_resp);
    
    Response *rsp = alloc_response(ret_code, checkin_resp, strlen(checkin_resp) + 1);
    // Return "roadrunner checkin" in response
    return rsp;
}

/**
 * @brief Command to have RoadRunner sleep for a specified number of seconds.
 * @param cmd the command structure
 * @return a Response structure
 */
Response *sleep_command(Command *cmd)
{
    // Perform sleep and return base msg with how long the agent was commanded to sleep
    int ret_code = 0;
    char* sleep_arg = cmd->args;
    int arg_len = cmd->args_len;
    char buffer[50];
    char *base_msg;
    
    //char* base_msg = (char*)malloc(50);
    if(sleep_arg == NULL){
        ret_code = 1;
        base_msg = "arguments provided are NULL";
    }
    else if(strlen(sleep_arg) > 4){
        ret_code = 1;
        base_msg = "arguments are not of the correct type";
    }
    else{
        int sleep_num = atoi(sleep_arg);
        sleep(sleep_num);
        sprintf(buffer, "road runner slept for %d second(s)", sleep_num);
        base_msg = buffer;
    }
    
    Response *rsp = alloc_response(ret_code, base_msg, strlen(base_msg) + 1);
    return rsp;
}
