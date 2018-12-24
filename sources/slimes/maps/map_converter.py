#!/usr/bin/python
# -*- coding: utf-8 -*-
import os, pip, subprocess, sys

import configparser

try:
    import pandas
except ImportError:
    subprocess.check_call(["python", "-m", "pip", "install", "pandas"])
    import pandas

config = configparser.ConfigParser()
config.read("config.ini")

map_file = pandas.read_csv(config.get("parameters", "map", fallback = False).strip("\""), header = None, index_col = False)

file = open(config.get("parameters", "map", fallback = False).strip("\"").strip(".csv")+".map", "w+b")
file.write(int(len(map_file.columns)).to_bytes(1, "little"))
file.write(int(len(map_file.index)).to_bytes(1, "little"))
file.write(int(config.get("parameters", "tile_blocking_limit", fallback = False)).to_bytes(1, "little"))
file.write(int(config.get("parameters", "tile_set", fallback = False)).to_bytes(1, "little"))
file.write(int(config.get("parameters", "tile_set_tiles_amount", fallback = False)).to_bytes(1, "little"))
file.write(int(config.get("parameters", "music", fallback = False)).to_bytes(1, "little"))

for x in enumerate(map_file.columns):
    for y in map_file.index:
        #print(str(x[1])+" "+str(y)+" "+str(map_file[y][x[1]]))
        file.write(int(map_file[y][x[1]]).to_bytes(1, "little"))

file.close()
