/**
 * sys.c contains all of the functionality for the system commands.
 * @file sys.c
 */

#include <sys.h>


#define PLACEHOLDER "replace"
#define PLACEHOLDER_SIZE 7

// processlist helper functions
static uint32_t is_pid_folder(char *dir);
static uint32_t parse_pid_stat(char *proc_pid_dir, pid_stat_t *pid_stats);
static uint32_t parse_pid_owner(char *proc_pid_dir, pid_stat_t *pid_stats);
static uint32_t parse_pid_cmdline(char *proc_pid_dir, pid_stat_t *pid_stats);
static uint32_t return_plist_line(int pid, char *proc_line);

// netstat helper functions
static uint32_t parse_conn_line(char *line, tcp_conn_t *connections);
static char *hex_to_ipaddr(u_int32_t ip_h);
static void free_connections(tcp_conn_t *connections);
static void print_connections(tcp_conn_t *connections, char *print_line);


/************************INSTRUCTIONS*****************************

Build 4 commands:
    hostname                Returns hostname
    invoke                  Returns shell command output
    proclist                Returns process list or proc info
    netstat                 Returns netstat

Hostname Functions:
    hostname_command

Invoke Functions
    invoke_command

Proclist Functions:
    process_list_command
        is_pid_folder
        return_pslist
            parse_pid_stat
            parse_pid_owner
            parse_pid_cmdline

Netstat Functions:
    get_netstat_command
        parse_conn_line
            hex_to_ipaddr
        print_connections
        free_connections

If you want to make use of the test harness, do not remove the MACROs. 
The macros will perform the required functionality for the function. 
See the defined macros in sys.h for more information.

*****************************END**********************************/

/**
 * @brief Returns hostname of host machine
 * @param cmd (in) a pointer to the command
 * @return Response where the message is the hostname
 * @return HOSTNAME_ERROR_MSG on error
 */
Response *hostname_command(Command *cmd)
{
    uint32_t ret_code = 0;
    char hostname[BUFF_MAX + 1];
    Response *rsp = NULL;

    // Get hostname
    HOSTNAME_MACRO(hostname, BUFF_MAX + 1, ret_code);
    if(ret_code == 0){
        rsp = alloc_response(ret_code, hostname, strlen(hostname) + 1);
    }
    else{
        ret_code = 1;
        rsp = alloc_response(ret_code, HOSTNAME_ERROR_MSG, sizeof(HOSTNAME_ERROR_MSG) + 1);
    }
    return rsp;
}

/**
 * @brief Builds formatted process list in one heap buffer and passed to Response
 * arg[1] = "" (empty) - Return full process list
 * arg[1] = pid - Return process information for just 1 pid
 * 
 * @param cmd (in) Command selected with args
 * @return Response* Formatted process list on success
 * @return Response* PROCESS_ERROR_MSG on error
 */
Response *process_list_command(Command *cmd)
{
    char* process_list = NULL;
    char* proc_line = NULL;
    long pid_max = 0;
    int pid = 0;
    //process_list = (char*)calloc(1, PROCESS_LINE_MAX + 1); **
    char* dir = NULL;
    //dir = calloc(1, 16); **
    //proc_line = (char*)calloc(1, PROCESS_LINE_MAX + 1); **
    //pid = (char*)calloc(1, sizeof(long));

    // Use this Format for your output header to (needed to pass the test)
    // Uncomment the line below
    snprintf(process_list, PROCESS_LINE_MAX + 1, "%-10s %-8s %-8s %-20s %s\n", "OWNER", "PID", "PPID", "PNAME", "CMDLINE");

    if(cmd->args_len == 1){
        FILE* fp = fopen("/proc/sys/kernel/pid_max", "r");
        printf("%d\n", __LINE__);
        char* spid_max = calloc(1, 8);
        fgets(spid_max, 8, fp);
        printf("%d\n", __LINE__);
        pid_max = atol(spid_max);
        fclose(fp);

        int i;
        for(i=1000; i<pid_max; i++){
            printf("ITER %d\n", i);
            printf("%d\n", strlen(process_list));
            sprintf(dir, "/proc/%d", i);
            if(is_pid_folder(dir) == 1){
                pid = i;
                printf("pid %d\n", pid);
                int errcode = return_plist_line(pid, proc_line);
                if(errcode == 0){
                    Response *rsp = alloc_response(1, "error: failed to get process list", 35);    
                    return rsp;
                }
                if(strlen(process_list) > 8000){
                    break;
                }
                strcat(process_list, proc_line);
            }
        }
    }
    else{
        pid = (int)strtol(cmd->args, NULL, 10);
        printf("%d\n", __LINE__);
        int errcode = return_plist_line(pid, proc_line);
        // printf("%d\n", __LINE__);
        // printf("%s\n", proc_line);
        if(errcode == 0){
            Response *rsp = alloc_response(1, "error: failed to get process list", 35);    
            return rsp;
        }
        strcat(process_list, proc_line);
    }
    
    // Return process list for just 1 pid
    //  or
    // process all directories
    // Return process list
    free(pid);

    
    Response *rsp = alloc_response(0, process_list, PROCESS_LINE_MAX + 1);    
    return rsp;
}

/**
 * @brief Checks if folder contains all digits
 * @param entry (in) dirent structure - returned from readdir
 * @return uint32_t Returns 1 on success, 0 on failure
 */
static uint32_t is_pid_folder(char *dir)
{   
    DIR* check_dir;
    check_dir = opendir(dir);
    printf("Checkdir: %p\n", check_dir);
    if(check_dir == NULL){
        return 0;
    }
    closedir(check_dir);
    return 1;
}

/**
 * @brief Loads struct pid_stat_t with information for 1 process from /proc
 *  processid -> pid
 *  parentpid -> ppid
 *  process name -> comm
 *  State of process -> state
 *
 * @param proc_pid_dir (in) Directory of process
 * @param pid_stats (out) pointer to struct pid_stat_t
 * @return Returns 0 if unable to process information
 * @return Returns 1 if successful
 */
static uint32_t parse_pid_stat(char *proc_pid_dir, pid_stat_t *pid_stats)
{
    // read process statistics /proc/<pid>/stat
    char *raw_pid_stats = NULL;
    uint32_t contents_size = 0;
    printf("LINE %d\n", __LINE__);
    //raw_pid_stats = calloc(1, PROCESS_LINE_MAX + 1); **
    /* Open and read /proc/<pid>/stat, Output are statistics, delimited by " "
     *  "man proc" for details */
    strcat(proc_pid_dir, "/stat");
    FILE* fp = fopen(proc_pid_dir, "r");
    fgets(raw_pid_stats, PROCESS_LINE_MAX, fp);
    fclose(fp);
    //contents_size = read_file("/proc/1/stat", &raw_pid_stats);
    //READ_PROC_MACRO(proc_pid_dir, &raw_pid_stats, contents_size);
    printf("PID stats %s\n", raw_pid_stats);
    printf("content size %d\n", contents_size);
    if(contents_size == 1){
        return 0;
    }
    // load pid_stats with information
    char* eptr;
    char* pid = strtok(raw_pid_stats, " ");
    printf("LINE %s\n", pid);
    pid_stats->pid = (uint32_t)strtol(pid, &eptr, 10);
    printf("LINE %d\n", __LINE__);
    char* file_name = strtok(NULL, " ");
    strcpy(pid_stats->comm, file_name);
    char* status = strtok(NULL, " ");
    pid_stats->state = status[0];
    char* ppid = strtok(NULL, " ");
    pid_stats->ppid = (uint32_t)strtol(ppid, &eptr, 10);



    return 1;
}

/**
 * @brief Opens /proc/<pid>/loginuid to determine owner of process.
 * Sometimes loginuid returns -1 -> sets owner to "unk"
 * Loads pid_stats->owner with the owner of the process
 * NOTE: Loginuid isn't always accurate to the owner of the process
 * 
 * @param proc_pid_dir (in) loginuid path (ex. /proc/<pid>/loginuid)
 * @param pid_stats (out) struct with process information - defined in sys.h
 * @return uint32_t returns 0 if unable to parse owner
 * @return uint32_t returns 1 on success
 */
static uint32_t parse_pid_owner(char *proc_pid_dir, pid_stat_t *pid_stats)
{
    // Initialize Variables
    char *owner = NULL;
    char pw_name[20];
    uint32_t contents_size = 0;
    uid_t uid;
    strcat(proc_pid_dir, "/loginuid");
    printf("PARSE OWNER %s\n", proc_pid_dir);
    // call getpwuid(uid)
    //READ_LOGINID_MACRO(proc_pid_dir, &owner, contents_size); 
    FILE* fp = fopen(proc_pid_dir, "r");
    fgets(&owner, 10, fp);
    fclose(fp);
    if(contents_size == 0){
        return 0;
    }

    uid = atol(owner);
    // struct passwd* pwd = calloc(1, sizeof(struct passwd)); **
    //pwd = getpwuid(uid); **
    // strncpy(pw_name, pwd->pw_name, OWNER_MAX + 1); **

    // strcpy(pid_stats->owner, pw_name); **

    
    return 1;
}

/**
 * @brief Opens /proc/<pid>/cmdline to get the exact command that kicked off the process
 * Loads pid_stats->cmdline with the command
 * 
 * @param proc_pid_dir (in) path to cmdline (ex. /proc/<pid>/cmdline)
 * @param pid_stats (out) struct with process information - defined in sys.h
 * @return uint32_t returns 0 if unable to parse cmdline
 * @return uint32_t returns 1 on success
 */
static uint32_t parse_pid_cmdline(char *proc_pid_dir, pid_stat_t *pid_stats)
{
    // Initialize variables
    char *cmdline = NULL;
    uint32_t contents_size = 0;

    // read proc_dir and returns the cmdline string
    //READ_CMDLINE_MACRO(proc_pid_dir, &cmdline, contents_size);
    strcat(proc_pid_dir, "/cmdline");
    FILE* fp = fopen(proc_pid_dir, "r");
    fgets(&cmdline, 128, fp);
    fclose(fp);
    if(contents_size == 0){
        return 0;
    }

    strncpy(pid_stats->cmdline, cmdline, CMDLINE_MAX + 1);
    return 1;
}

/**
 * @brief Returns a formatted line with all corresponding pid information 
 * @param pid (in) process id (string of digits)
 * @param proc_line (out) formatted string with all process information
 * @return uint32_t length of proc_line (0 on failure)
 * *NOTE: Caller needs to free return
 */
static uint32_t return_plist_line(int pid, char *proc_line)
{
    printf("PID %d\n", pid);
    // pid_stat_t* pid_stats = calloc(1, sizeof(pid_stat_t)); **
    char print_line[255];
    char* dir = NULL;
    // *dir = calloc(1, 16);
    sprintf(dir, "/proc/%d", pid);
    printf("%s\n", dir);
    // int errcode = is_pid_folder(dir);
    // if(errcode == 0){
    //     return 0;
    // }
    // strcat(dir, "/stat");
    // printf("%s\n", dir); **
    // int errcode = parse_pid_stat(dir, pid_stats); **
    // if(errcode == 0){ **
    //     return 0; **
    // } **
    // sprintf(dir, "/proc/%d", pid); **
    // errcode = parse_pid_owner(dir, pid_stats); **
    // if(errcode == 0){ **
    //     return 0; **
    // } **
    // sprintf(dir, "/proc/%d", pid); **
    // errcode = parse_pid_cmdline(dir, pid_stats); **
    // if(errcode == 0){ **
    //     return 0; **
    // } **
    // // Format process line for return
    // snprintf(proc_line, PROCESS_LINE_MAX, "%-10s %8d %8d %-20s %s\n",
    //          pid_stats->owner,
    //          pid_stats->pid,
    //          pid_stats->ppid,
    //          pid_stats->comm,
    //          pid_stats->cmdline); **

    free(dir);

    return 1;
}

/**
 * @brief Calls Popen to execute shell commmand, not built for interactive cmds
 * 
 * @param cmd (in) 
 * @return Response* Returns command output on success or failure
 */
Response *invoke_command(Command *cmd)
{
    Response *rsp = NULL;
    FILE *cmd_output;
    char buffer[1024];
    char* shell_cmd = cmd->args;
    printf("shell cmd %s\n", shell_cmd);

    cmd_output = popen(shell_cmd, "r");
    fgets(buffer, 1024, cmd_output);
    pclose(cmd_output);
    // Use the man pages to learn about he Popen command
    // Use the function to invoke the user specified command
    // Read the output from the command into a buffer and return it to the user
    // in a response
    rsp = alloc_response(0, buffer, strlen(buffer) + 1);
    return rsp;
}

/**
 * @brief Opens /proc/net/tcp and sends current tcp connections
 * 
 * @param cmd (in)
 * @return Response* returns formatted tcp socket information on success
 * @return Response* returns NETSTAT_ERROR_MSG on failure
 */
Response *get_netstat_command(Command *cmd)
{ 
    char *tcp_stream = NULL;
    uint32_t contents_size = 0;
    tcp_conn_t *connections = NULL;
    char netstat_buff[BUFF_MAX]; 
    char print_line[255];
    FILE* fp = NULL;

    // Set up header for netstat, use this line for the test harness
    // Uncomment the line below
    snprintf(netstat_buff, BUFF_MAX, "%-21s %-21s %-10s %-20s %10s\n", "LOCAL", "REMOTE", "STATUS", "OWNER", "INODE");

    connections = (tcp_conn_t*)calloc(1, sizeof(tcp_conn_t));
    connections->next = NULL;
    fp = fopen("/proc/net/tcp", "r");
    if(fp == NULL){
        Response *rsp = alloc_response(1, NETSTAT_ERROR_MSG, 30);
        return rsp;
    }

    tcp_conn_t* pIter = NULL;

    char* line = calloc(1, BUFF_MAX);
    fscanf(fp, "%[^\n] ", line);

    for(pIter = connections; pIter!=NULL; pIter->next) {
        int errcode = fscanf(fp, "%[^\n] ", line);
        if(errcode == EOF){
            break;
        }
        tcp_conn_t* pNew = (tcp_conn_t*)calloc(1, sizeof(tcp_conn_t));

        errcode = parse_conn_line(line, pIter);
        if(errcode == 0){
            Response *rsp = alloc_response(1, NETSTAT_ERROR_MSG, 30);
            return rsp;
        }
        

        print_connections(pIter, print_line);

        strcat(netstat_buff, print_line);

        pIter->next = pNew;

        pIter = pNew;

    }
    pIter->next = NULL;

    free(line);
    fclose(fp);
    
    free_connections(connections);
    // set up response
    Response *rsp = alloc_response(0, netstat_buff, BUFF_MAX + 1);
    return rsp;
}

/**
 * @brief Parse network connections from /proc/net/tcp and set relevant fileds in tcp_conn_t struct
 * 
 * @param line (in) Line of network connections from /proc/net/tcp (1 network connection at a time)
 * @param connections (out) linked list structure to hold network info for each connection
 * @return uint32_t returns 1 on success
 * @return uint32_t returns 0 on failure
 */
static uint32_t parse_conn_line(char *line, tcp_conn_t *connections)
{
    uint32_t uid = 0;
    struct passwd *pwd = NULL;

    //sl  local_address rem_address  st tx_queue rx_queue tr tm->when retrnsmt   uid  timeout inode
    //0: 3600007F:0035 00000000:0000 0A 00000000:00000000 00:00000000 00000000   102        0 9964 1 0000000049c35940 100 0 0 10 5

    strtok(line, " "); // index
    char* parse_local_addr = strtok(NULL, ":");
    char* parse_local_port = strtok(NULL, " ");
    char* parse_remote_addr = strtok(NULL, ":");
    char* parse_remote_port = strtok(NULL, " ");
    char* parse_state = strtok(NULL, " ");
    strtok(NULL, " "); //tx_queue rx_queue
    strtok(NULL, " "); //tr tm->when
    strtok(NULL, " "); //retrnstm
    char* parse_uid = strtok(NULL, " ");
    strtok(NULL, " "); //timeout
    char* parse_inode = strtok(NULL, " ");
    //rest is ignored

    char converted_local_ip[16];
    strncpy(converted_local_ip, hex_to_ipaddr((int)strtol(parse_local_addr, NULL, 16)), 16);

    char converted_remote_ip[16];
    strncpy(converted_remote_ip, hex_to_ipaddr((int)strtol(parse_remote_addr, NULL, 16)), 16);

    uid = atoi(parse_uid);

    //GET_UID_MACRO(uid, pwd);
    pwd = getpwuid(uid);
    if(pwd->pw_name == NULL){
        return 0;
    }

    if(connections != NULL){
        strncpy(connections->local_addr, converted_local_ip, 16);
        connections->local_port = (int)strtol(parse_local_port, NULL, 16);
        strncpy(connections->remote_addr, converted_remote_ip, 16);
        connections->remote_port = (int)strtol(parse_remote_port, NULL, 16);
        connections->state = (int)strtol(parse_state, NULL, 16);
        strcpy(connections->owner, pwd->pw_name);
        connections->inode = (ino_t)atol(parse_inode);
    }
    // fill out relevan information in the connections struct

    return 1;
}

/**
 * @brief Format a netstat connection
 * 
 * @param connections (in) structure with connection information - defined in sys.h
 * @param print_line (out) formatted connection line
 */
static void print_connections(tcp_conn_t *connections, char *print_line)
{
    /* Format line ("-" makes it left justified)
    * Need this format for the test harness
    * Uncomment the line below */

    int state = connections->state;
    char status[11];

    switch(state){
        case 1: strncpy(status, "ESTAB", 10);
            break;
        case 2: strncpy(status, "SYNSENT", 10);
            break;
        case 3: strncpy(status, "SYNRECV", 10);
            break;
        case 4: strncpy(status, "FINWAIT1", 10);
            break;
        case 5: strncpy(status, "FINWAIT2", 10);
            break;
        case 6: strncpy(status, "TIMEWAIT", 10);
            break;
        case 7: strncpy(status, "CLOSE", 10);
            break;
        case 8: strncpy(status, "CLOSEWAIT", 10);
            break;
        case 9: strncpy(status, "LASTACK", 10);
            break;
        case 10: strncpy(status, "LISTENING", 10);
            break;
        case 11: strncpy(status, "CLOSING", 10);
            break;
        case 12: strncpy(status, "NEWSYN", 10);
            break;
        default: strncpy(status, "DIFF", 10);
            break;
    }
    snprintf(print_line, BUFF_MAX, "%15s:%-5d %15s:%-5d %-10s %-20s %10ld\n",
                connections->local_addr,
                connections->local_port,
                connections->remote_addr,
                connections->remote_port,
                status,
                connections->owner,
                connections->inode);
    
    return;
}

/**
 * @brief Free connection linked list
 * 
 * @param connections (in) structure with connection information - defined in sys.h
 */
static void free_connections(tcp_conn_t *connections)
{
    tcp_conn_t* pIter = connections;
    tcp_conn_t* pNextEntry = pIter;
    if(pIter != NULL){
        do{
            pIter = pIter->next;
            free(pNextEntry);
            pNextEntry = pIter;
        }while(pNextEntry != NULL);
    }

    return;
}

/**
 * @brief convert network order hex to ipv4 string notation
 *       This function is useful to make the hex representation found in
 *       /proc/net/tcp human readable
 * 
 * @param ip_h (in) hex value found in /proc/net/tcp
 * @return char* ipv4 string notation
 */
static char *hex_to_ipaddr(uint32_t ip_h)
{    
    struct in_addr addr;
    addr.s_addr = ip_h;

    return inet_ntoa(addr);
}

