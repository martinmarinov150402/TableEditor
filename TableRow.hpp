#ifndef TABLE_ROW
#define TABLE_ROW

#include <iostream>
#include "TableRecord.hpp"
#include "string.h"

class TableRow
{
    private:
        int size;
        int capacity;
        TableRecord** records;
        void copy(TableRow const& other);

    public:
        TableRow();
        TableRow(String& row);
        ~TableRow();
        TableRow& operator=(TableRow const& other);
        TableRow(TableRow const& other);
        void WriteOnStream(std::ostream& out);
};


#endif