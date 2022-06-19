#ifndef TABLE_DEF
#define TABLE_DEF

#include "TableRow.hpp"
#include "string.h"

const int DEFAULT_T_CAPACITY = 10;

class Table
{
    private:
        String file;
        TableRow** tableContent;
        int sizeRows;
        int capacityRows;
        void copy(Table const& other);
        double calculateFormula(int _row, int _col);

    public:

        Table();
        Table(String fileName);
        Table(Table const& other);
        Table& operator=( Table const& other);
        ~Table();
        void printTable();
        void addRow(String& row);
        bool save();
        bool saveAs(String& _file);
        bool setRecord(int _row, int _col, String& record);

};

#endif