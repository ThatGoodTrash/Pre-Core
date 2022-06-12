/**
 * files.c contains all of the functionality for the download and upload commands.
 * @file files.c
 */

#include <files.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <string.h>
#include <arpa/inet.h>

static uint32_t deserialize_upload_file_path(char *upload_args, char **file_path_out);
static uint32_t deserialize_upload_file_contents(char *upload_args, uint32_t file_path_len, char **contents_out);

/**
 * @brief opens file specified by parameter passed, puts the contents in contents_out and returns the size.
 * @param filename filename to open
 * @param contents_out a NULL pointer that will contain the contents of the file or NULL on error
 * @return an integer representing the number of bytes read
 */ 
uint32_t read_file(char *filename, char **contents_out)
{
    uint32_t read_counter;
    FILE* fp = NULL;

    fp = fopen(filename, "r");
    if(NULL == fp){
        return 0;
    }
    fseek(fp, 0L, SEEK_END);
    long int file_size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    char* result_out = (char*)malloc(file_size + 1);
    fgets(result_out, file_size + 1, fp);

    read_counter = file_size + 1;
    
    *contents_out = result_out;
    fclose(fp);
    return read_counter;
}

/**
 * @brief Write the contents of a stream to a specified file.
 * @param filename the name of the file to write to
 * @param contents a pointer to the contents that will be written
 * @param contents_size the size of the contents
 * @return returns the number of bytes written to the file
 */
uint32_t write_file(char *filename, char *contents, uint32_t contents_size)
{
    uint32_t write_counter = 0;
    FILE* fp = NULL;

    // open the file handle in write bytes mode
    fp = fopen(filename, "w");
    if(NULL == fp){
        return 0;
    }
    else if(contents_size == 0){
        return 0;
    }
    fputs(contents, fp);
    // write contents
    write_counter = contents_size;

    return write_counter;
}

/**
 * @brief Download the file specified in the Command args.
 * @param cmd the download command with arguments
 * @return a Response where the message is the file byte stream
 */
Response *download_file_command(Command *cmd)
{

    Response *rsp = NULL;
    FILE* fp = NULL;
    char* file_name = cmd->args;
    int ret_code = 0;
    
    // open the file handle in read bytes mode
    fp = fopen(file_name, "r");
    if(NULL == fp){
        rsp = alloc_response(1, "error downloading file", 24);
        return rsp;
    }
    fseek(fp, 0L, SEEK_END);
    long int file_size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    // Send contents
    char* file_contents = (char*)malloc(file_size + 1);
    fgets(file_contents, file_size + 1, fp);

    rsp = alloc_response(ret_code, file_contents, file_size + 1);
    free(file_contents);

    return rsp;

}

// int deserialize_byteArray(int iOffset, char* pSourceBuffer, char* pOut, int iLength){
//         memcpy(pOut, &pSourceBuffer[iOffset], iLength);
//         //*pOut = ntohl(*pOut);
//         return (sizeof(char) * iLength);
// }

// int deserialize_int(int iOffset, char* pSourceBuffer, unsigned int *pOut){
//         memcpy(pOut, &pSourceBuffer[iOffset], sizeof(uint32_t));
//         *pOut = ntohl(*pOut);
//         return sizeof(uint32_t);
// }

/**
 * @brief deserialize the file path and file path length from upload arguments.
 * @param upload_args the full upload arguments passed in the command structure
 * @param file_path_out a NULL pointer that will contain the file path on success or NULL on error
 * @return the length of the file path
 */
static uint32_t deserialize_upload_file_path(char *upload_args, char **file_path_out)
{
    uint32_t file_path_len;
    
    int iBufferOffset = 0;
    iBufferOffset += deserialize_int(iBufferOffset, upload_args, &file_path_len);
    iBufferOffset += deserialize_byteArray(iBufferOffset, upload_args, *file_path_out, file_path_len);
    // refer to the README.md to inform how to deserialize just the upload path

    return file_path_len;
}

/**
 * @brief deserialize the file contents and contents length from upload arguments.
 * @param upload_args the full upload arguments passed in the command structure
 * @param file_path_len length of the already deserialize file path
 * @param contents_out a NULL pointer that will contain the file contents on success or NULL on error
 * @return the length of the file path
 */
static uint32_t deserialize_upload_file_contents(char *upload_args, uint32_t file_path_len, char **contents_out)
{
    uint32_t content_len = 0;
    // refer to the README.md to inform how to deserialize just the file contents
    int iBufferOffset = 4 + file_path_len;
    char* file_path = NULL;


    //file_path = calloc(128, sizeof(char)); 
    // iBufferOffset += deserialize_int(iBufferOffset, upload_args, &file_path_len);
    // iBufferOffset += deserialize_byteArray(iBufferOffset, upload_args, &file_path, file_path_len + 1);
    // printf("LINE %d\n", __LINE__);
    // printf("file path %s\n", &file_path);
    iBufferOffset += deserialize_int(iBufferOffset, upload_args, &content_len);
    iBufferOffset += deserialize_byteArray(iBufferOffset, upload_args, *contents_out, content_len);


    return content_len;
}

/**
 * @brief Upload the file specified in the command arguments.
 * @param cmd the command structure
 * @return a response indicating upload success or failure
 */
Response *upload_file_command(Command *cmd)
{
    Response *rsp = NULL;
    
    // Deserialize path and contents
    uint32_t args_len = cmd->args_len;
    char* args = cmd->args;
    uint32_t file_path_len;
    uint32_t content_len;
    char* file_path = NULL;
    char* file_contents = NULL;
    file_path = calloc(128, sizeof(char));
    file_contents = calloc(1024, sizeof(char));

    file_path_len = deserialize_upload_file_path(args, &file_path);

    content_len = deserialize_upload_file_contents(args, file_path_len, &file_contents);
    if(content_len == NULL){
        rsp = alloc_response(1, "error with upload file contents", 32);
        free(file_path);
        free(file_contents);
        return rsp;
    }
    // Write file

    FILE* fp = fopen(file_path, "w");
    if(NULL == fp){
        rsp = alloc_response(1, "error with upload file path", 29);
        free(file_path);
        free(file_contents);
        return rsp;
    }

    int errcode = fputs(file_contents, fp);
    if(errcode == EOF){
        rsp = alloc_response(1, "error with upload file contents", 32);
        free(file_path);
        free(file_contents);
        return rsp;
    }

    fclose(fp);

    free(file_path);
    free(file_contents);

    rsp = alloc_response(0, "upload successful", 19);
    
    return rsp;
}
