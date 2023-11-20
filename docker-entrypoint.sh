#!/bin/bash
set -e

cd $(dirname $0)

[ -d build ] && rm -rf build

# Build and bundle the app test code
cmake -S . -B build
cmake --build build
twilio microvisor:apps:bundle build/app/mv-app-test.bin build/app/mv-app-test.zip

