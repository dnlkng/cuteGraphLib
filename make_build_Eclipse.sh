#!/bin/bash

# Creates Eclipse CDT4 Makefiles build via cmake

# TODO:		modify the vars
# AUTHOR:	Daniel König, mail@daniel-koenig.net

export GRAPHVIZ_INCLUDE_DIR="/usr/local/include/graphviz"
export GRAPHVIZ_LIBRARY_DIR="/usr/local/lib"

BUILD_FOLDER="build_Eclipse"

if [ ! -d $BUILD_FOLDER ]; then
	mkdir $BUILD_FOLDER
fi

cd $BUILD_FOLDER
cmake -G "Eclipse CDT4 - Unix Makefiles" ../source
mkdir Client/generated_from_moc
mkdir Client/generated_from_ui
