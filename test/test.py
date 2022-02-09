from cmath import exp
import pytest
import os
from random import choices
from string import ascii_uppercase

filename = "test/tmp"

def launch_tee(text, mode, expected_text=None):
    os.system("echo {} | ./tee {} {}".format(text, mode, filename))
    assert os.path.isfile(filename)
    with open(filename) as f:
        if expected_text is None:
            expected_text = text + "\n"
        assert f.read() == expected_text

def generate_random_string(size):
    return ''.join(choices(ascii_uppercase, k=size))

@pytest.mark.parametrize("mode", ["","-a"])
@pytest.mark.parametrize("size", [10, 100, 1000, 10000, 100000])
def test_file_creation(mode, size):
    text = generate_random_string(size)
    launch_tee(text, mode)
    os.remove(filename)
        
@pytest.mark.parametrize("mode", ["","-a"])
@pytest.mark.parametrize("size", [10, 100, 1000, 10000, 100000])
def test_file_exists(mode, size):
    first_text = generate_random_string(size)
    launch_tee(first_text, mode)

    second_text = generate_random_string(size)
    expected_text = None

    if mode == "-a":
        expected_text = "{}\n{}\n".format(first_text, second_text)

    launch_tee(second_text, mode, expected_text)
    os.remove(filename)
    
