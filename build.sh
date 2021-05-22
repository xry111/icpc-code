#!/bin/sh

clang-format -i $(find -name "*.cc")
lualatex main.tex
