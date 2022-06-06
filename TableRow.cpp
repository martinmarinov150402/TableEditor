#include <iostream>
#include "TableRow.hpp"
#include "TableRecord.hpp"
#include "checkType.hpp"
#include "NumberRecord.hpp"
#include "RationalRecord.hpp"

int countItems(String tr)
{
    int items = 1;
    for(int i = 0; i < tr.Size(); i++)
    {
        if(tr[i] == ',')
        {
            items++;
        }
    }
    return items;
}
TableRow::TableRow()
{
    size = 0;
    capacity = 10;
    records = new TableRecord*[capacity];
}

TableRow::~TableRow()
{
    delete[] records;
}

void TableRow::copy(TableRow const& other)
{
    size = other.size;
    capacity = other.capacity;
    records = new TableRecord*[capacity];
    for(int i = 0; i < size; i++)
    {
        records[i] = other.records[i];
    }
}
TableRow::TableRow(String& row)
{
    String tmp = "";
    int itemsC = countItems(row);
    records = new TableRecord*[itemsC];
    int idx = 0;
    for(int i = 0; i < row.Size(); i++)
    {
        if(row[i] != ',')
        {
            tmp.append(row[i]);
        }
        else
        {
            int type = checkType(tmp);
            switch(type)
            {
                case TYPE_NUMBER:
                {
                    records[idx] = new NumberRecord();
                    break;
                }
                case TYPE_RATIONAL:
                {
                    records[idx] = new RationalRecord();
                    break;
                }
                case TYPE_STRING:
                {
                    records[idx] = new StringRecord();
                    break;
                }
                case TYPE_UNDEF:
                {
                    break;
                }
            
            }
        }
    }
}
TableRow::TableRow(TableRow const& other)
{
    copy(other);
}
TableRow& TableRow::operator=(TableRow const& other)
{
    if(this != &other)
    {
        delete[] records;
        copy(other);
    }
    return *this;
}