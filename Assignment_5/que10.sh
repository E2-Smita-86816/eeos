#!/bin/bash

echo "Enter the number of terms:"
read n

a=1
b=1

echo "Fibonacci series up to $n terms:"

for (( i=0; i<n; i++ ))
do
    echo -n "$a " 
    fibo=$((a + b))  
    a=$b        
    b=$fibo       
done

echo "$a"

