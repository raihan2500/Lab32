#include<stdio.h>
#include<stdlib.h>

int main(){
	int *p = malloc(5*sizeof(int));
  *p = 5;
  p++;
  *p = 10;
  p--;
  p++;
  printf("%d\n", *p);
}