#!/bin/bash

echo "Enter file or directory):"
read name

	if [ -f $name ]
	then
		echo " Size: $(du -sh $name)"
	elif [ -d $name ] 
	then 
		ls $name
	else
		echo "File not exists!"
	
	fi
