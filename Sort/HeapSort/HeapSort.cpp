#include<iostream>
#include<fstream>
#include<cstring>
void printarray(int *ptr, int length);
int createheap(int *ptr, const int length);
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

void printarray(int *ptr, int length)
{
	for (int i=0; i< length; i++) 
		cout << ptr[i] << " ";
	cout << endl;
}

int minheapsort(int *ptr, const int length)
{
	createheap(ptr, length);
	for (int i = length - 1; i > 0; i--) {
		swap(ptr[0], ptr[i]);
		printarray(ptr, length);
		minheapify(ptr, 0, i);
	}
	return 0;
}

int createheap(int *ptr, const int length)
{
	int i;

	for (i = length - 1; i > 0; i--) {
		//swap(ptr[i], ptr[0]);
		minheapify(ptr, i, length);
	}
	return 0;
}

int minheapify(int *ptr, int i, int length)
{
	//int temp = ptr[i];
	int child = 2 * i + 2;

	if (child < length) {
		//compare left & right
		if (ptr[child] >= ptr[child - 1]) {
			//parent < larger child
			if (ptr[i] < ptr[child]) {
				swap(ptr[i], ptr[child]);
				minheapify(ptr, i, length);
			}
		} else {
			// parent < larger child
			if (ptr[i] < ptr[child - 1]) {
				swap(ptr[i], ptr[child - 1]);
				minheapify(ptr, child - 1, length);
			}
		}
	} else if((child - 1) < length) { //left exist
		if (ptr[i] < ptr[child - 1]) { //compare parent with left
			swap(ptr[i], ptr[child - 1]);
			minheapify(ptr, child - 1, length);
		}
	}
			
	return 0;
}
