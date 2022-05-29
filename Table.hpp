#ifndef TABLE_DEF
#define TABLE_DEF

#include "TableRecord.hpp"
#include "string.h"

const int DEFAULT_T_CAPACITY = 10;

enum Types
{
    Double,
    Int,
    Str,
};
class Table
{
    private:
        TableRecord** tableContent;
        int sizeRows;
        int sizeCols;
        int capacityRows, capacityCols;

    public:
        Types getType();
        Table();
        Table(Table const& other);
        Table& operator=( Table const& other);
        ~Table();
        bool readFromFile(String fileName);

};

#endif