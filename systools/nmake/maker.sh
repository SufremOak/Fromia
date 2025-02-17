#!/usr/local/bin/bash

autocompiler = make
fromiaLibs = ./clibs/*.h
cc = gcc
defaultArgs = -Wall -Wextra -I/usr/lib/nmake

if [ -z $1 ]; then
    echo "Usage: nmake <filename>"
    exit 1
fi

while getopts ":c:l:a:" opt; do
    case $opt in
        c)
            cc=$OPTARG
            ;;
        l)
            fromiaLibs=$OPTARG
            ;;
        a)
            defaultArgs=$OPTARG
            ;;
        \?)
            echo "Invalid option: -$OPTARG" >&2
            exit 1
            ;;
        :)
            echo "Option -$OPTARG requires an argument." >&2
            exit 1
            ;;
    esac
done
shift $((OPTIND -1))

filename=$1

$cc $defaultArgs $fromiaLibs -o ${filename%.*} $filename