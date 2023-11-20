#!/bin/bash
set -e

cd $(dirname $0)

[ -d build ] && rm -rf build

# Place these here so dependencies are checked
# even if the take the BUILD_ONLY path (GitHub Action)
cmake -S . -B build
cmake --build build
twilio microvisor:apps:bundle build/app/mv-app-test.bin build/app/mv-app-test.zip

