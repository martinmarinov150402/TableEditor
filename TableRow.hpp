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
        int maxRLength;

    public:
        bool setRecord(int idx, String& record);
        int getSize() {return size;}; 
        TableRow();
        TableRow(String& row);
        ~TableRow();
        TableRow& operator=(TableRow const& other);
        TableRecord*& operator[](int idx);
        TableRow(TableRow const& other);
        void WriteOnStream(std::ostream& out);
        int getMaxRLength() { return maxRLength;};
};


#endif