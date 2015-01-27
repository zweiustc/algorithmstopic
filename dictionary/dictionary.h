
struct RowDataFormat
{
    int col_count;
    struct ColumnDataFormat;
    struct RowDataFormat *next;
}

struct ColumnDataFormat
{
    DataType type;
    int repetitions;
    struct ColumnDataFormat *next;
}

enum DataType {
                  T_int =1,
                  T_float =2,
                  T_char_ptr =3};


class Vocabulary
{
    public:
        read_row_data(const char *);
        read_whole_vocabulary(FILE * file);
    private:
        struct RowDataFormat RowData;       
}
