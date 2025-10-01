#!/bin/bash
echo "# Building the App..."
./build.sh || exit $?

echo "# Running the App..."
./run_app.sh $* || exit $?