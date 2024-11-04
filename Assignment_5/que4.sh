#!/bin/bash


echo "Enter the number :"
read num

i=1

while [ $num % $i -eq 0 ]
do
	echo "Not prime"
	i=`expr $i+1`
done

