#include<stdio.h>
#include<string.h>

#define FILE_LEN	10000;
int analysis(char *buffer, FILE *fp, int *length)
{
	int i;
	
		
}

int main() 
{
    int ret = -1;
	FILE *fp = NULL;
	char *buffer;
    int length;

    //read the file
    fp = fopen("source_file.txt", 'rb');
	if(fp == NULL) {
        printf("open source file error!\n");
		return ret;
	}
/*
 *
 *
 *
 */
	length = ftell(fp);
	fseek(fp, 0L, SEEK_set);

	//malloc buffer for content
	buffer = (char *) malloc(length);
    if(buffer == NULL) {
		printf("malloc failed !\n");
		return ret;
	}
	memset(buffer, 0, length);
	fread(buffer, length, 1, fp);

    //create the result file
    fp = fopen("result_data", "wb");
	if (fp == NULL) {
		printf("failed to open result_data file\n");
		return ret;
	}
    
	//begin the analysis
	ret = analysis_data(buffer, fp, &length);

	return ret;
	
        
	

}
