#!/usr/bin/python
# -*- coding: utf-8 -*-

object_type = {"INVISIBLE": 0,
               "NPC": 1}

bytecode = {"WARP": 0,
            "MESSAGE": 1,
            "SCRIPT": 2}

direction = {"RIGHT": 0,
             "UP": 1,
             "LEFT": 2,
             "DOWN": 3}

flag = {"NO_FLAG": 255}

import configparser, os, pip, subprocess, sys

try:
    from lxml import etree
except ImportError:
    subprocess.check_call(["python", "-m", "pip", "install", "lxml"])
    from lxml import etree

try:
    import pandas
except ImportError:
    subprocess.check_call(["python", "-m", "pip", "install", "pandas"])
    import pandas

from io import StringIO

parameter = sys.argv[1]

config = configparser.ConfigParser()
config.read(parameter.strip(".tmx")+".ini")

map_file = pandas.read_csv(StringIO(etree.parse(parameter).xpath("/map/layer/data")[0].text), header = None, index_col = False)

file = open(parameter.strip(".tmx")+".map", "w+b")
file.write(int(len(map_file.columns)-1).to_bytes(1, "big"))
file.write(int(len(map_file.index)).to_bytes(1, "big"))
file.write(int(config.get("parameters", "tileset_id", fallback = False)).to_bytes(1, "big"))
file.write(int(config.get("parameters", "tiles_amount", fallback = False)).to_bytes(1, "big"))
file.write(int(config.get("parameters", "tiles_block_id", fallback = False)).to_bytes(1, "big"))
file.write(int(config.get("parameters", "tiles_anim_start_id", fallback = False)).to_bytes(1, "big"))
file.write(int(config.get("parameters", "tiles_anim_end_id", fallback = False)).to_bytes(1, "big"))
file.write(int(config.get("parameters", "music_id", fallback = False)).to_bytes(1, "big"))

for x in enumerate(map_file.columns[:-1]):
    for y in map_file.index:
        #print(str(x[1])+" "+str(y)+" "+str(map_file[y][x[1]]-1))
        file.write(int(map_file[y][x[1]]-1).to_bytes(1, "big"))

if "events" in config.sections():
    # amount of events
    file.write(int(len(config.items("events"))).to_bytes(1, "big"))
    # events x, y, id
    for i in range(len(config.items("events"))):
        file.write(int({**flag}.get([item[1] for item in config.items("events")][i].split(",")[0], [item[1] for item in config.items("events")][i].split(",")[0])).to_bytes(1, "big"))
        file.write(int([item[1] for item in config.items("events")][i].split(",")[1]).to_bytes(1, "big"))
        file.write(int([item[1] for item in config.items("events")][i].split(",")[2]).to_bytes(1, "big"))
        file.write(int([item[0] for item in config.items("events")][i]).to_bytes(1, "big"))

    # data length, data/bytecode
    last_event_length = 0
    for i in range(len(config.items("events"))):
        file.write(int(len([item[1] for item in config.items("events")][i].split(","))-3).to_bytes(1, "big"))
        for j in range(len([item[1] for item in config.items("events")][i].split(","))-3):
            file.write(int({**object_type, **bytecode, **direction}.get([item[1] for item in config.items("events")][i].split(",")[j+3], [item[1] for item in config.items("events")][i].split(",")[j+3])).to_bytes(1, "big"))
else:
    file.write(int(0).to_bytes(1, "big"))

if "objects" in config.sections():
    # amount of objects
    file.write(int(len(config.items("objects"))).to_bytes(1, "big"))
    # objects flag, x, y, id
    for i in range(len(config.items("objects"))):
        file.write(int({**flag}.get([item[1] for item in config.items("objects")][i].split(",")[0], [item[1] for item in config.items("objects")][i].split(",")[0])).to_bytes(1, "big"))
        file.write(int([item[1] for item in config.items("objects")][i].split(",")[1]).to_bytes(1, "big"))
        file.write(int([item[1] for item in config.items("objects")][i].split(",")[2]).to_bytes(1, "big"))
        file.write(int([item[0] for item in config.items("objects")][i]).to_bytes(1, "big"))

    # data length, data/bytecode
    last_event_length = 0
    for i in range(len(config.items("objects"))):
        file.write(int(len([item[1] for item in config.items("objects")][i].split(","))-3).to_bytes(1, "big"))
        for j in range(len([item[1] for item in config.items("objects")][i].split(","))-3):
            file.write(int({**object_type, **bytecode, **direction}.get([item[1] for item in config.items("objects")][i].split(",")[j+3], [item[1] for item in config.items("objects")][i].split(",")[j+3])).to_bytes(1, "big"))
else:
    file.write(int(0).to_bytes(1, "big"))

if "npc" in config.sections():
    # amount of NPCs
    file.write(int(len(config.items("npc"))).to_bytes(1, "big"))
    # npc flag, x, y, id
    for i in range(len(config.items("npc"))):
        file.write(int({**flag}.get([item[1] for item in config.items("npc")][i].split(",")[0], [item[1] for item in config.items("npc")][i].split(",")[0])).to_bytes(1, "big"))
        file.write(int([item[1] for item in config.items("npc")][i].split(",")[1]).to_bytes(1, "big"))
        file.write(int([item[1] for item in config.items("npc")][i].split(",")[2]).to_bytes(1, "big"))
        file.write(int([item[0] for item in config.items("npc")][i]).to_bytes(1, "big"))

    # data length, data/bytecode
    last_event_length = 0
    for i in range(len(config.items("npc"))):
        file.write(int(len([item[1] for item in config.items("npc")][i].split(","))-3).to_bytes(1, "big"))
        for j in range(len([item[1] for item in config.items("npc")][i].split(","))-3):
            file.write(int({**object_type, **bytecode, **direction}.get([item[1] for item in config.items("npc")][i].split(",")[j+3], [item[1] for item in config.items("npc")][i].split(",")[j+3])).to_bytes(1, "big"))
else:
    file.write(int(0).to_bytes(1, "big"))

file.close()

print("ok")
