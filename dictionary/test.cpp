#include<cstring>
#include<iostream>
#include<fstream>
using namespace std;
#define MaxBytePerRow 256
/*
struct RowDataFormat
{
    int col_count;
    struct ColumnDataFormat;
    struct RowDataFormat *next;
}
*/


enum DataType {
                  T_int =1,
                  T_float =2,
                  T_char_ptr =3};

struct ColumnDataFormat
{
    DataType type;
    int repetitions;
    struct ColumnDataFormat *next;
};


class Vocabulary
{
    public:
        int read_file(string *filename);
        //int read_row_data(const ifstream file, struct ColumnDataFormat *DataFormat);
        int read_row_data(const char *row_data);
        //read_whole_vocabulary(FILE *file);
    private:
        struct ColumnDataFormat RowData;       
};

int Vocabulary::read_file(string *filename)
{
    string src_file = *filename; 
    ifstream infile;
    const char *row_data;
    string data;
    
    infile.open(src_file.c_str(), ios::in);
    if (!infile) {
        cout << "failed to open the file\n";
        return 1;
    }

    while (getline(infile, data)) {
        
        cout << data<< endl;
        row_data = data.c_str();
        cout << row_data << endl;;
    }
    cout << "open success!\n";
}
int Vocabulary::read_row_data(const char *row_data)
{
    char test_row_data[MaxBytePerRow];
    //while(getline(file, MaxBytePerRow)) {
         //while(DataFormat)
    //}
}

//#define src "/home/work/dictionary/data.log"
int main()
{
    ifstream infile;
    //char row_data[MaxBytePerRow];
    const char *row_data;
    string src_file;
    string data;
    int a = 1;
    Vocabulary test;
    //input source file
    cout << "please input source file name\n";
    cin >> src_file;
 
    test.read_file(&src_file);



    return 0;
}
