#ifndef TABLE_DEF
#define TABLE_DEF

#include "TableRow.hpp"
#include "string.h"

const int DEFAULT_T_CAPACITY = 10;

class Table
{
    private:
        TableRow* tableContent;
        int sizeRows;
        int capacityRows;
        void copy(Table const& other);

    public:
        Table();
        Table(String fileName);
        Table(Table const& other);
        Table& operator=( Table const& other);
        ~Table();

};

#endif