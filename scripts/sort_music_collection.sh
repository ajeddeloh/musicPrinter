#!/bin/bash
#Sample script showing how to use muprint to generate paths and use those paths
#To sort music. This version uses copy instead of move for safety
#Run from the project root or change ./muprint to be approriate

#TODO: make these arguments
SRC_DIR='/media/Music/'
DST_DIR='/media/MusicSorted'


move_file() {
    # $1 - file to move
    # $2 - where to move it
    local dst="$(./muprint -s 'A%ua' -s 't%uf' -r _ "$2/%uA/%ub/%t.%e" "$1")"
    echo "$dst"
    mkdir -p "$(dirname "$dst")"
    cp "$1" "$dst"
}

#make move_file available to subshells
export -f move_file

find "$SRC_DIR" -type f -exec sh -c 'move_file "$1" "$2"' _ {} "$DST_DIR" \; 
