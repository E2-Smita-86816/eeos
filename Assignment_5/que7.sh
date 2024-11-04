#!/bin/bash

echo "Enter the number :"
read num

if [ $num -gt 0 ]
then 
	echo "Number is positive"
else
	echo "Number is negative"
fi
