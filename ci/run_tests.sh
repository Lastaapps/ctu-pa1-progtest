#!/bin/bash

./test_ci.sh 1>/dev/null

TAG="CI_TEST"
filePattern="main.c"
archive="sample.tgz"
tests="mytests"
outFile="test_run.out"
sample="sample"
progtestOut="main"

for file in $(find .. -name "$filePattern" )
do

	echo "$TAG: Testing file: $file"

	folder=${file%"$filePattern"}
	name=${filePattern}

	if [[ -f "$folder$archive" ]]; then

		./progtest.sh "$file" "$folder$archive"
		code=$?

		rm -r "$folder$sample"
		rm -r "$folder$progtestOut"

		if [[ code -ne 0 ]]; then
			echo "$TAG: Progtest test failed for file $file" 1>&2
			exit 1
		fi

		if [[ -d "$folder$tests" ]]; then

			./progtest.sh "$file" "$folder$tests"
			code=$?

			rm -r "$folder$progtestOut"

			if [[ code -ne 0 ]]; then
				echo "$TAG: My tests failed for file $file" 1>&2
				exit 2
			fi
		fi

	else

		./assert_run.sh ${file}

		code=$?
		if [[ code -ne 0 ]]; then
			echo
			echo "$TAG: Assertion test failed for file $file" 1>&2
			exit 3
		fi
	fi

	echo
	echo
done

echo "$TAG: All tests passed!"
exit 0


