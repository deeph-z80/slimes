#!/usr/bin/python
# -*- coding: utf-8 -*-

import configparser, os, pip, subprocess, sys

try:
    import PIL.Image
except ImportError:
    subprocess.check_call(["python", "-m", "pip", "install", "pillow"])
    import PIL.Image

print("---\nGamebuino Meta indexed image converter - deeph\n---\n")

for i in range(1, len(sys.argv)):
    if sys.argv[i] == "-i":
        i += 1
        try:
            input_image_name = sys.argv[i]
            input_image = PIL.Image.open(input_image_name)
        except AttributeError:
            print("Unsupported image format : "+sys.argv[i])
            exit()
        except (IndexError, FileNotFoundError):
            print("No input image specified.")
            exit()
    elif sys.argv[i] == "-p":
        i += 1
        try:
            palette_image = PIL.Image.open(sys.argv[i])
        except AttributeError:
            print("Unsupported palette image format : "+sys.argv[i])
            exit()
        except (IndexError, FileNotFoundError):
            print("No input palette image specified.")
            exit()
        if palette_image.size != (16, 1):
            print("Wrong palette format (must be 16×1 px) : "+sys.argv[i])
            exit()
    elif sys.argv[i] == "-o":
        i += 1
        try:
            output_file = sys.argv[i]
        except IndexError:
            print("No output file specified.")
            exit()
        try:
            file = open(output_file, "w")
        except IOError:
            print("Cannot write "+output_file)
            exit()

try:
    input_image
    palette_image
    output_file
except NameError:
    print("Wrong syntax, use :")
    print("-i [image] : input image file")
    print("-p [palette] : input palette image (must be 16×1 px)")
    print("-o [file] : output file")
    exit()

file.write("const uint8_t "+os.path.splitext(os.path.basename(input_image_name))[0]+"_data[] = {\n")
file.write("  "+str(input_image.size).strip("()")+",  // sprites width & height\n")
file.write("  1,0,    // sprites amount lower & upper 8-bit\n")
file.write("  0,      // frames loop (0 = no animation)\n")
file.write("  14,     // transparent color (14 = pink)\n")
file.write("  1,      // color mode (1 = indexed)\n")

palette_image = palette_image.convert("RGB")
palette = []
for x in range(0, 16):
    palette.append(palette_image.getpixel((x, 0)))
palette_image = palette_image.convert(mode = "P", palette = PIL.Image.ADAPTIVE, colors = 16)

input_image = input_image.convert("RGB")
input_image = input_image.quantize(palette = palette_image)
input_image = input_image.convert("RGB")

width, height = input_image.size
for y in range(0, height):
    file.write("  0x")
    for x in range(0, width):
        file.write(str(format(palette.index(input_image.getpixel((x, y))), "x")))
        if x % 2:
            if x != width-1:
                file.write(",0x")
        elif x == width-1:
            file.write("0")
        if x == width-1 and y != height-1:
            file.write(",")
    file.write("\n")
file.write("};\nImage "+os.path.splitext(os.path.basename(input_image_name))[0]+"("+os.path.splitext(os.path.basename(input_image_name))[0]+"_data);")
file.close()

print("File correctly converted.")
