#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <sys/resource.h>
#include<string.h>
//int last(int N);
//float timeval_subtract(struct timeval *tv1, struct timeval *tv2);

float timeval_subtract(struct timeval *tv1, struct timeval *tv2)
{
	return ((tv1->tv_sec - tv2->tv_sec) +
		((float) (tv1->tv_usec - tv2->tv_usec)) / 1000000);
}

int last(long N)
{
	int i;
	struct timeval time_start;
	struct timeval user_start;
	struct timeval system_start;
    struct rusage r;
    struct timeval time_end;
	struct timeval user_end;
	struct timeval system_end;

	//init time
    gettimeofday(&time_start, 0);
    memset(&r, 0, sizeof(struct rusage));
    getrusage(RUSAGE_SELF, &r);
	user_start = r.ru_utime;
	system_start = r.ru_stime;

	//last for some time
	for(i=0; i < N; i++);
 
    gettimeofday(&time_end, 0);
    getrusage(RUSAGE_SELF, &r);	
	user_end = r.ru_utime;
	system_end = r.ru_stime;

	printf("time: %5.2f/%5.2f/%5.2f\n", 
			timeval_subtract(&time_end, &time_start),
			timeval_subtract(&user_end, &user_start),
			timeval_subtract(&system_end, &system_start));
		
	return 0;
}

int main()
{
	long  N = 900000000;
	clock_t start, end;
	double duration;
	
	start = clock();
	last(N);
	end = clock();

	duration = (double) (end - start) / CLOCKS_PER_SEC;

	printf("duration time by clock: %f seconds\n", duration);

	return 0;
						
}
