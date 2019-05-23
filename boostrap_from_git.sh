#!/bin/bash

# Get submodule repositories
git submodule init
git submodule update

# Setup the project using GNU autotools
aclocal
autoreconf
automake --add-missing
