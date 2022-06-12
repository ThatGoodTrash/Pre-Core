from threading import Thread
import threading
from typing import Callable, Tuple, List
from ipaddress import ip_address, IPv4Address 
from enum import Enum
import socket

class LogLevels(Enum):
    DEBUG = 10
    INFO = 5
    ERROR = 1

class Controller:
    def __init__(self, server, log_level): 
        if not server:
            return

        self.a = server[0]
        self.p = server[1]
        self.loglevel = log_level
        self.h = []
        self.r = False

    @property
    def address(self):
        return str(self.__address)

    @address.setter
    def address(self, value):
        if type(value) != str:
            raise Exception("Bad IPv4 address")
        try :
            self.__address: IPv4Address  = ip_address(value)
        except Exception as e:
            raise e

    @property
    def port(self):
        return self.__port

    @port.setter
    def port(self, value: int):
        if not isinstance(value, int):
            raise Exception("Bad port value")
        if not (10000 < value < 20000):
            raise Exception("Controller port needs to be between 10000 and 20000")
        self.__port = value

    def add_e_h(self, item):
        if not item:
            return False
        self.h.append(item)
        return True

    @property
    def loglevel(self):
        return self.__loglevel

    @loglevel.setter
    def loglevel(self, value):
        self.__loglevel = value

    def runner(self):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        try:
            s.bind((self.a, self.p))
            s.listen(10)
        except Exception as e:
            self.r = False
            return

        while self.r:
            _c, _a = s.accept()
            with _c:
                print('Connected by', _a)
                while True:
                    data = _c.recv(1024)
                    if not data: 
                        break
                    for x in self.h:
                        x(_c, data)
                    
    def start_server(self):
        if self.r:
            return False
        self.r = True
        _t = threading.Thread(target = self.runner, args = ())
        _t.start()
        return self.r

    def stop_server(self):
        self.r = False