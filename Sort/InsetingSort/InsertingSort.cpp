#include<iostream>
#include<fstream>
#include<cstring>
int sort(int *ptr, const int length);
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
	
	insertingsort(a, count);	

    for(int i=0;i<count;i++)
        cout << a[i] << " ";
	cout <<endl;
	return 0;
}


int insertingsort(int *ptr, const int length)
{
	int i, j, temp;

	for(i=2;i<length;i++) {
		temp = ptr[i];
		j = i-1;
		while (temp < ptr[j] && j >0) {
			ptr[j+1] = ptr[j];
			j = j-1;
		}
		ptr[j+1] = temp;
	}
	return 0;
}
