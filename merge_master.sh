#!/bin/bash


target=master
git checkout "$target"

branches=$(git branch | egrep '^\s*(cv|hw)' | tr '[:space:]' $'\n'| tr -s $'\n' | grep '.')

for branch in ci $branches
do
	echo Merging $branch
	git merge --no-ff -m "mrg: Merge '$branch' into 'master'" "$branch"

done
