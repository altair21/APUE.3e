#include "apue.h"
#include <limits.h>

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif

#define OPEN_MAX_GUESS 256

long open_max(void) {
	struct rlimit *rlp;
	if (openmax == 0) {
		if ((openmax = sysconf(_SC_OPEN_MAX)) < 0 || openmax == LONG_MAX) {
			int rl = getrlimit(RLIMIT_NOFILE, rlp);
			if (rl < 0) {
				err_sys("get rlimit failure");
			} else {
				if ((*rlp).rlim_max == RLIM_INFINITY )
					openmax = OPEN_MAX_GUESS;
				else
					openmax = (*rlp).rlim_max;
			}
		}
	}
	printf("OPEN_MAX is %ld\n", openmax);
	return openmax;
}

int main(void) {
	open_max();
	exit(0);
}