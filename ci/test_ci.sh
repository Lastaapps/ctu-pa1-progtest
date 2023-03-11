#!/bin/bash

TAG="CI_TEST"
outFile="test_ci.out"

./compile.sh 1>&2 2>/dev/null
code=$?
if [ $code -eq 0 ]; then
	echo "$CI_TEST: intput failed, code: $code!" 1>&2
	rm "$outFile"
	exit 1;
fi

./compile.sh tests/correct.c "$outFile" 1>&2 2>/dev/null
code=$?
if [ $code -ne 0 ]; then
	echo "$CI_TEST: corrent failed, code: $code!" 1>&2
	rm "$outFile"
	exit 2;
fi

./compile.sh tests/fail.c "$outFile" 1>&2 2>/dev/null
code=$?
if [ $code -eq 0 ]; then
	echo "$CI_TEST: fail failed, code: $code!" 1>&2
	rm "$outFile"
	exit 3;
fi

./compile.sh tests/pedantic.c "$outFile" 1>&2 2>/dev/null
code=$?
if [ $code -eq 0 ]; then
	echo "$CI_TEST: pedantic failed, code: $code!" 1>&2
	rm "$outFile"
	exit 4;
fi

echo "$TAG: All tests passed!"

rm "$outFile"
exit 0;



