#!/bin/sh

cmake -B build
pushd build/src
make
popd

