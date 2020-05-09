#!/bin/sh
#RUN THIS FROM ROOT DIRECTORY

if [ $# -eq 0 ]; then
  echo "Need to supply 1 argument"
  return
fi
echo "Creating example: $1"

pushd examples
  cp -r template $1
popd
  