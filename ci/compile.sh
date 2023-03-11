#!/bin/bash

TAG="Compile"

if [[ $# -ne 2 || -z ${1} ]]; then
	echo "$TAG: Wrong input, usage is $0 toCompile.c" 1>&2
	exit 1
fi

in="$1"
out="$2"

responce=$(g++ -std=c++14 -Wall -Wshadow --pedantic -Wno-long-long -Werror -g -fsanitize=address -o "${out}" "${in}" 2>&1)
result=$?

if [ 0 -ne $result ]; then
	echo "$TAG: Wrong result code: $result" 1>&2
	exit 2
fi

if [ ! -z "${responce}" ]; then
	echo "$TAG: Error output" 1>&2
	echo "$responce"
	exit 3
fi

exit 0




