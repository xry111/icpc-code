#!/bin/sh

clang-format -i $(find -name "*.cc")
latexmk --lualatex main.tex
