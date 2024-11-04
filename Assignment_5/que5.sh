#!/bin/bash

echo -e -n "Enter num1 : "
read n1

echo -e -n "Enter num2 : "
read n2

echo -e -n "Enter num3 : "
read n3

if [ $n1 -gt $n2 ]
then
	echo "Num 1 is greater : $n1"
elif [ $n2 -gt $n3 ]
then
	echo "Num 2 is greater : $n2"
else
	echo "Num 3 is greater : $n3"
fi
