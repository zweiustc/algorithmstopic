#include <stdio.h>
int main()
{
    FILE *fp;
	char *path = "/home/zhangwei/opentest.log";
	fp = fopen(path, "w+");
	fprintf(fp, "tst");
	
	fclose(fp);
	return 0;

}
