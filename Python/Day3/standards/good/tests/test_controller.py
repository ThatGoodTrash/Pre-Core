import socket
import time
import logging

try:
    from src import controller
except Exception as e:
    print("Running tests")
    import sys
    import os
    sys.path.append(os.path.dirname(os.path.realpath(__file__)) + "/../src")
    import controller

def test_controller_constructor():
    conn_details = ("127.0.0.1", 12001)
    log_level = controller.LogLevels.DEBUG
    t_controller = controller.Controller(conn_details, log_level)

    assert t_controller.address == conn_details[0]
    assert t_controller.port == conn_details[1]

def test_controller_runs():
    conn_details = ("127.0.0.1", 12002)
    log_level = controller.LogLevels.DEBUG
    t_controller = controller.Controller(conn_details, log_level)

    result = t_controller.start_server()
    assert result == True

    s = socket.socket()
    time.sleep(1)
    s.connect(conn_details)

    s.close()

    t_controller.stop_server()

def echo_handler(s: socket.socket, data: bytes) -> None:
    s.sendall(data)

def test_controller_handlers():
    conn_details = ("127.0.0.1", 12003)
    log_level = controller.LogLevels.DEBUG
    t_controller = controller.Controller(conn_details, log_level)

    result = t_controller.add_event_handler(echo_handler)
    assert result == True

    result = t_controller.start_server()
    assert result == True

    s = socket.socket()
    time.sleep(1)
    s.connect(conn_details)
    s.sendall(b"HELLO")

    recv_data = s.recv(5)
    assert recv_data == b"HELLO"

    s.close()
    t_controller.stop_server()
