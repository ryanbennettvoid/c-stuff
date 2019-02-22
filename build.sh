#!/bin/bash
PROG=$1
DIR="./src/$PROG"

if [ -z $PROG ]; then
  echo "no program specified"
  exit 1
fi

if [ ! -d $DIR ]; then
  echo "dir $DIR does not exist"
  exit 1
fi

gcc -O3 -o ./bin/$PROG $DIR/main.c