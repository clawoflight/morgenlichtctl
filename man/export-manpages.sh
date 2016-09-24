#!/bin/sh
DIR="$(dirname $0)"
echo "Writing man-pages to '$DIR' ..."

if (test -x /usr/bin/go-md2man); then
	go-md2man -in="$DIR"/morgenlichtctl.1.md -out="$DIR"/morgenlichtctl.1

else
	echo "Please install 'go-md2man'."
	exit 1
fi
