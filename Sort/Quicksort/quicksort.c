#include<stdio.h>
#include<stdlib.h>

#define N 15

void showqueue(int *queue, int len)
{
	int i = len;
	while (i--)
		printf("%d ", queue[i]);
	printf("\n");
	
}

void swap(int *a, int *b)
{
	int temp = 0;
	
	temp = *a;
	*a = *b;
	*b = temp;
}
void quicksort(int *queue, int start, int end)
{
	int mid = 0;
	
	if (start >= end) return;
	/* decomposition the queue */
	mid = partition(queue, start, end);
	quicksort(queue, start, mid-1);
	quicksort(queue, mid+1, end);		
}

int partition(int *queue, int start, int end)
{
	int temp = 0, i = 0, j = 0;
	
	temp = queue[end];
	i = start - 1;
	
	for (j = start; j < end; j++) {
		if (queue[j] < temp) {
			i++;
			swap(&queue[i], &queue[j]);
		}
	}
	swap(&queue[i+1], &queue[end]);

	return (i+1);	
	
}



int main()
{
	int queue[N] = {0};
	int i = 0;

	/* create the queue */
	for (i = 0; i < N; i++)
		queue[i] = random() % 20;
    /* show the queue */
	showqueue(queue, N);	
	
	quicksort(queue, 0, N-1);
	
	/* show the sorted queue*/
	showqueue(queue, N);
	return 1;

}
