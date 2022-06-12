from threading import Thread
import threading
from typing import Callable, Tuple, List
from ipaddress import IPv6Address, ip_address, IPv4Address
from enum import Enum
import time
import socket


class LogLevels(Enum):
    DEBUG = 10
    INFO = 5
    ERROR = 1


class Controller:
    def __init__(self, server: Tuple[str, int], log_level: LogLevels):
        if not server:
            return

        self.address = server[0]
        self.port = server[1]
        self.loglevel = log_level
        self.__handlers: List[Callable[[socket.socket, bytes], None]] = []
        self.__running = False

    @property
    def address(self) -> str:
        return str(self.__address)

    @address.setter
    def address(self, value: str):
        if type(value) != str:
            raise Exception("Bad IPv4 address")
        try:
            self.__address: IPv4Address | IPv6Address = ip_address(value)
        except Exception as e:
            raise e

    @property
    def port(self) -> int:
        return self.__port

    @port.setter
    def port(self, value: int):
        if not isinstance(value, int):
            raise Exception("Bad port value")
        if not (10000 < value < 20000):
            raise Exception("Controller port needs to be between 10000 and 20000")
        self.__port = value

    def add_event_handler(
        self, handler: Callable[[socket.socket, bytes], None]
    ) -> bool:
        """
        Add an event (Callable) for whenever the server receives data. The event handler will receive
        the socket and the bytes that were received

        Returns whether the event handler was added
        """
        if not handler:
            return False
        self.__handlers.append(handler)
        return True

    @property
    def loglevel(self) -> LogLevels:
        return self.__loglevel

    @loglevel.setter
    def loglevel(self, value: LogLevels):
        self.__loglevel = value

    def __runner(self) -> None:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        try:
            s.bind((self.address, self.port))
            s.listen(10)
        except Exception as e:
            self.__running = False
            return

        while self.__running:
            conn, addr = s.accept()
            with conn:
                print("Connected by", addr)
                while True:
                    data = conn.recv(1024)
                    if not data:
                        break
                    for handler in self.__handlers:
                        handler(conn, data)

    def start_server(self) -> bool:
        """Have the server bind and start listening for connections."""
        if self.__running:
            return False
        self.__running = True
        _t = threading.Thread(target=self.__runner, args=())
        _t.start()
        return self.__running

    def stop_server(self) -> None:
        """Ask the server to close the socket and stop"""
        self.__running = False
