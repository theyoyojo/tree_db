#!/bin/bash

# Get submodule repositories
cd lil_test
git submodule init
git submodule update
cd ..

# Setup the project using GNU autotools
aclocal
autoreconf
automake --add-missing
