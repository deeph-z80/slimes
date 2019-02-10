#!/usr/bin/python
# -*- coding: utf-8 -*-

import configparser, os, pip, subprocess, sys

parameter = sys.argv[1]
config = configparser.ConfigParser()
config.read(parameter)

file = open(parameter.replace(".ini", ".str"), "w+b")

if "strings" in config.sections():
    # string length, string data
    for i in range(len(config.items("strings"))):
        file.write(int(len([item[1] for item in config.items("strings")][i].replace("\\n", "\n"))).to_bytes(1, "big"))
        file.write([item[1] for item in config.items("strings")][i].replace("\\n", "\n").encode("utf_8"))

file.close()

print("ok")
