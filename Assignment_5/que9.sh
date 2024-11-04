#!/bin/bash

echo "Enter the number:"
read num

fact=1
i=1

while [ $i -le $num ] 
do
    fact=`expr $fact \* $i` 
    i=`expr $i + 1` 
done

echo "Factorial is $fact" 
	
