#!/usr/bin/python
# -*- coding: utf-8 -*-

import configparser, os, pip, subprocess, sys

from io import StringIO

config = configparser.ConfigParser()
config.read("strings.ini")

file = open("strings.str", "w+b")

if "strings" in config.sections():
    # string length, string data
    for i in range(len(config.items("strings"))):
        file.write(int(len([item[1] for item in config.items("strings")][i])).to_bytes(1, "big"))
        #file.write(int([item[1] for item in config.items("strings")][i]).to_bytes(1, "big"))
        file.write([item[1] for item in config.items("strings")][i].encode())

file.close()

print("ok")
input()
