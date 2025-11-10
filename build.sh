#!/bin/sh

cc -o mandelbrot main.c -Wall -Wextra -I./raylib-5.5_linux_amd64/include/ -L./raylib-5.5_linux_amd64/lib/ -l:libraylib.a -lm
