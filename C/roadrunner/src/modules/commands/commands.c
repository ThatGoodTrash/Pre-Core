/**
 * commands.c contains all of the functionality for serializeing and deserializing commands and responses.
 * @file commands.c
 */

#include <commands.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdbool.h>
#include <utils.h>

int deserialize_int(int iOffset, char* pSourceBuffer, unsigned int *pOut){
        memcpy(pOut, &pSourceBuffer[iOffset], sizeof(uint32_t));
        *pOut = ntohl(*pOut);
        return sizeof(uint32_t);
}

int deserialize_byteArray(int iOffset, char* pSourceBuffer, char* pOut, int iLength){
        memcpy(pOut, &pSourceBuffer[iOffset], iLength);
        //*pOut = ntohl(*pOut);
        return (sizeof(char) * iLength);
}

/**
 * @brief Deserialize a message stream of bytes into a Command structure.
 * @param msg_size (in) the total message stream size
 * @param msg_stream (in) a pointer to the message stream
 * @return a pointer to a Command structure or NULL on error
 */
Command *deserialize_command(uint32_t msg_size, char *msg_stream)
{
    // Validate command received
    int total_size = 0;
    int cmd_length = 0;
    char cmd[128] = {'\0'};
    int args_length = 0;
    char args[128] = {'\0'};
    int iBufferOffset = 0;
    //alloc command for struct
    //Command* result = NULL;
    //memset(&result, 0, sizeof(result));
    // Get bytes
    iBufferOffset += deserialize_int(iBufferOffset, msg_stream, &total_size);

    if(total_size != msg_size){
        return NULL;
    }
    iBufferOffset += deserialize_int(iBufferOffset, msg_stream, &cmd_length);
    iBufferOffset += deserialize_byteArray(iBufferOffset, msg_stream, &cmd, cmd_length);
    iBufferOffset += deserialize_int(iBufferOffset, msg_stream, &args_length);
    iBufferOffset += deserialize_byteArray(iBufferOffset, msg_stream, &args, args_length);


    // convert from network to host byte order
    // store command in struct
    Command* result = alloc_command(cmd, cmd_length, args, args_length);
    
    return result;
}

/**
 * @brief Allocate the memory and store data in a new Command structure.
 * @param cmd (in) pointer to the cmd bytes
 * @param cmd_len (in) the size of the cmd
 * @param args (in) pointer to the args bytes
 * @param args_len (in) the size of the args
 * @return a pointer to an empty Command structure or NULL on error
 */
Command *alloc_command(char *cmd, uint32_t cmd_len, char *args, uint32_t args_len)
{
    Command *new_cmd = calloc(1, sizeof(Command));
    // if we get a null then there are memory issues and we need to bail
    if (new_cmd == NULL)
    {
        return new_cmd;
    }
    new_cmd->cmd = calloc(cmd_len, sizeof(char));
    memcpy(new_cmd->cmd, cmd, cmd_len);
    new_cmd->cmd_len = cmd_len;
    new_cmd->args = calloc(args_len, sizeof(char));
    memcpy(new_cmd->args, args, args_len);
    new_cmd->args_len = args_len;
    return new_cmd;
}

/**
 * @brief Free a Command structure and its components.
 * @param cmd a pointer to a Command structure
 */
void free_command(Command *cmd)
{
    if (cmd != NULL)
    {
        checkfree(cmd->cmd)
            checkfree(cmd->args)
                free(cmd);
    }
}

int serialize_int(unsigned long iData, char *pTargetBuffer)
{
    uint32_t iConverted = htonl(iData);
    memcpy(pTargetBuffer, &iConverted, sizeof(uint32_t));
    return sizeof(uint32_t);
}

int serialize_byteArray(char *pData, char *pTargetBuffer, unsigned int uiSize)
{
    memcpy(pTargetBuffer, pData, uiSize);
    return uiSize;
}

/**
 * @brief Serialize a Response structure into a byte stream.
 * @param rsp (in) a pointer to a Response structure
 * @param stream_out (out) a NULL char pointer where the stream will be passed back out
 * @return the total size of the stream
 */
uint32_t serialize_response(Response *rsp, char **stream_out)
{
    // initialize variables
    uint32_t total_size = 0;
    int ret_code = 0;
    char *message = NULL;
    int msg_len = 0;
    int iBufferOffset = 0;
    char* cBuffer = NULL;
    
    

    // calculate the total size of the message
    // memcpy(&total_size, rsp, sizeof(uint32_t));
    // total_size = htonl(total_size);
    ret_code = rsp->ret_code;
    msg_len = rsp->msg_len;
    message = rsp->msg;
    

    total_size += sizeof(uint32_t) * 3 + msg_len;

    cBuffer = (char*)calloc(1, total_size + 1);
    // Convert to network byte order
    // copy each part of the message into the stream
    iBufferOffset += serialize_int(total_size, cBuffer + iBufferOffset);
    iBufferOffset += serialize_int(ret_code, cBuffer + iBufferOffset);
    iBufferOffset += serialize_int(msg_len, cBuffer + iBufferOffset);
    iBufferOffset += serialize_byteArray(message, cBuffer + iBufferOffset, msg_len);
    printf("Msg_len: %d\n", msg_len);

    // total_size += ret_code + sizeof(message), + msg_len;
    
    *stream_out = cBuffer;
    //free(cBuffer);
    return total_size;
}

/**
 * @brief Allocate memory for a Response structure.
 * @param ret_code (in) the integer return code
 * @param msg (in) the message stream
 * @param msg_len (in) the size of the message stream
 * @return a pointer to a Response structure or NULL on error
 */
Response *alloc_response(int32_t ret_code, char *msg, uint32_t msg_len)
{
    Response *rsp;
    rsp = calloc(1, sizeof(Response));

    // if we get a null then there are memory issues and we need to bail
    if (rsp == NULL)
    {
        return rsp;
    }

    rsp->ret_code = ret_code;
    rsp->msg_len = msg_len;

    // need to include the null terminator
    rsp->msg = calloc(msg_len, sizeof(char));
    memcpy(rsp->msg, msg, msg_len);

    return rsp;
}

/**
 * @brief free a Response structure and its components.
 * @param rsp pointer to a Response structure
 */
void free_response(Response *rsp)
{

    // check to see if the Response structure is NULL
    if (rsp != NULL)
    {
        // free the message stream
        checkfree(rsp->msg)
            // free the whole structure
            free(rsp);
    }
}
