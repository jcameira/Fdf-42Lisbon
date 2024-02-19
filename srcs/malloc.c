#include <time.h>
#include <stdlib.h>

extern void	*__real_malloc(size_t size);

void	*__wrap_malloc(size_t size)
{
	srand(time(NULL));
	if (rand() % 2)
		return NULL;
	return __real_malloc(size);
}
