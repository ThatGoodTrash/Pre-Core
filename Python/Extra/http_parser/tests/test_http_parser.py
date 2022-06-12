from pathlib import Path
from ..exercises.parser import parse


sample_path = Path(__file__).parent / "../resources"


def test_sample1():
    with open(sample_path / "sample1.txt", "rb") as f:
        data = f.read()
        req = parse(data)
        assert req.method == "GET"
        assert req.version == "1.1"
        assert req.uri == "/files/fruit.txt"
        assert req.headers["Host"] == "eloquentjavascript.net"
        assert req.headers["User-Agent"] == "The Imaginary Browser"


def test_sample2():
    with open(sample_path / "sample2.txt", "rb") as f:
        data = f.read()
        req = parse(data)
        assert req.method == "GET"
        assert req.version == "1.1"
        assert req.uri == "/hello.htm"
        assert req.headers["Host"] == "www.tutorialspoint.com"
        assert (
            req.headers["User-Agent"]
            == "Mozilla/4.0 (compatible; MSIE5.01; Windows NT)"
        )
        assert req.headers["Accept-Language"] == "en-us"
        assert req.headers["Accept-Encoding"] == "gzip, deflate"
        assert req.headers["Connection"] == "Keep-Alive"


def test_sample3():
    with open(sample_path / "sample3.txt", "rb") as f:
        data = f.read()
        req = parse(data)
        assert req.method == "POST"
        assert req.version == "1.1"
        assert req.uri == "/cgi-bin/process.cgi"
        assert req.host == "www.tutorialspoint.com"
        assert (
            req.headers["User-Agent"]
            == "Mozilla/4.0 (compatible; MSIE5.01; Windows NT)"
        )
        assert req.headers["Host"] == "www.tutorialspoint.com"
        assert req.headers["Content-Type"] == "application/x-www-form-urlencoded"
        assert req.headers["Accept-Language"] == "en-us"
        assert req.headers["Accept-Encoding"] == "gzip, deflate"
        assert req.headers["Connection"] == "Keep-Alive"
        payload = req.body.parse_urlencoded()
        assert payload["foo"] == "one"
        assert payload["bar"] == "two"
        assert payload["baz"] == "three"


def test_sample4():
    with open(sample_path / "sample4.txt", "rb") as f:
        data = f.read()
        req = parse(data)
        assert req.method == "POST"
        assert req.version == "1.1"
        assert req.uri == "/cgi-bin/process.cgi"
        assert req.host == "www.tutorialspoint.com"
        assert (
            req.headers["User-Agent"]
            == "Mozilla/4.0 (compatible; MSIE5.01; Windows NT)"
        )
        assert req.headers["Host"] == "www.tutorialspoint.com"
        assert req.headers["Content-Type"] == "text/xml; charset=utf-8"
        assert req.headers["Content-Length"] == "94"
        assert req.headers["Accept-Language"] == "en-us"
        assert req.headers["Accept-Encoding"] == "gzip, deflate"
        assert req.headers["Connection"] == "Keep-Alive"
        payload = req.body.parse_raw()
        payload == (
            b'<?xml version="1.0" encoding="utf-8"?>\n'
            b'<string xmlns="http://clearforest.com/">string</string>'
        )


# Write your own tests and extend the parser for the rest of the samples
