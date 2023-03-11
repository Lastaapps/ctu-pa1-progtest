#!/bin/bash

outFile="compile_and_run.out"

./compile.sh $1 "$outFile"
compile_result="$?"

if [ "$compile_result" -eq 0 ]; then
	"./$outFile"
	code=$?

	rm "$outFile"

	exit $code
fi

rm "$outFile" 2>/dev/null

exit 1


