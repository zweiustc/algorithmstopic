#include<iostream>
#include<fstream>
#include<cstring>
int minheapsort(int *ptr, const int length);
int minheapify(int *ptr, int i, int length);
using namespace std;
int main()
{
    const int maxlength = 5;
    int count = 0;
    int a[maxlength] = {0};


    while(count < maxlength) {
        cout << "please input the num \n";
        cin >> a[count];
        if (a[count] == '0')
            break;
        count = count +1;
    }
	
	minheapsort(a, count);	

    for(int i=0;i<count;i++)
        cout << a[i] << " ";
	cout <<endl;
	return 0;
}


int minheapsort(int *ptr, const int length)
{
	int i;

	for (i=length-1;i>0;i--) {
		swap(ptr[i], ptr[0]);
		minheapify(ptr, i, length);
	}
	return 0;
}

int minheapify(int *ptr, int i, int length)
{
	int temp = ptr[i];
	int child = 2 * i;

	while(child < length) {
		if (child + 1 < length && ptr[child] > ptr[child+1])
			child++; //find the min child
		if (ptr[child] >= temp) break;
		//adjust the tree
		ptr[i] = ptr[child];
		i = child;
		child = 2 * i;
	}
	ptr[i] = temp;
	return 0;
}
