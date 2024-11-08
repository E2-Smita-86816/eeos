#include "rectangle.h"
#include "square.h"
#include "circle.h"
#include<stdio.h>
#include<math.h>
#include<stdlib.h>


int main(){
	printf("square area=%d\n",sq_area(5));
	printf("rectangle area=%d\n",rect_area(2,3));
	printf("circle area=%.2d\n",cir_area(2));
	return 0;
}
