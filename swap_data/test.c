#include <stdio.h>
#include <stdlib.h>
#include "swap_data.h"

int main(void)
{
	int a = 10, b = 20;
	printf("&a = %d, &b = %d\n", &a, &b);
	printf("Swap After:a = %d,b = %d.\n",a,b);
	swap_data(&a, &b);
	printf("Swap Before:a = %d,b = %d.\n",a,b);
	return 0;
}
