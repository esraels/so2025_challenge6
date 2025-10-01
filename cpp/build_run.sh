#!/bin/bash
./build.sh --std=c++17 -O3 || exit $?
./run_app.sh $* || exit $?