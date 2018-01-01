#!/bin/bash
rm -rf app
gcc -g -o app app.c graph/graph.c libfdr/libfdr.a -Wno-implicit-int
./app
