#include "swap_data.h"
void swap_data(int* x, int* y)
{
	printf("&x = %d, &y = %d\n", x, y);
	printf("x = %d, y = %d\n", *x, *y);
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}
