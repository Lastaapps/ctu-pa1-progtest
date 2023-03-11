!#/bin/bash

folder="mytests"
in="_in.txt"
out="_out.txt"

for file in ${folder}/*"${in}"
do

	file=${file#"$folder"}
	file=${file#"/"}
	outFile=${file%"${in}"}
	outFile="${outFile}${out}"

	printf "Writing from %s to %s\n" "$file" "$outFile"

	./main < "${folder}/${file}" > "${folder}/${outFile}"

done

