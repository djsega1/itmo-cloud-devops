import os
import requests

def test_app():
    assert requests.get("http://127.0.0.1:8000").text == os.environ.get("SECRET_VAR", "Hello world!")
