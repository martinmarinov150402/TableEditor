#include <iostream>
#include "TableRow.hpp"
#include "TableRecord.hpp"
#include "checkType.hpp"
#include "NumberRecord.hpp"
#include <cmath>
#include <algorithm>
#include "RationalRecord.hpp"
#include "StringRecord.hpp"
#include "FormulaRecord.hpp"

static void trim(String& param)
{
    bool started = false;
    String result;
    result = "";
    int start=0;
    int end=param.Size()-1;
    for(int i = 0; i < param.Size(); i++)
    {
        if(!started)
        {
            if(param[i] != ' ')
            {
                started = true;
                start = i;
            }
        }
    }
    for(int i = param.Size() - 1; i >= 0; i--)
    {
        if(param[i] != ' ')
        {
            end = i;
            break;
        }
    }
    for(int i = start; i <= end; i++)
    {
        result.append(param[i]);
    }
    param = result;
}
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
void TableRow::WriteOnStream(std::ostream& out)
{
    for(int i = 0; i < size; i++)
    {
        String data;
        if(records[i] != nullptr)
        {
            data = records[i]->getRawData();
            data.append('\0');
            for(int j = 0; j < data.Size(); j++)
            {
                out<<data[j];
            }
            out<<"\0";
        }
        if(i != size - 1) out<<", ";
        else out << "\n";
    }
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
TableRecord*& TableRow::operator[](int idx)
{
    return records[idx];
}
bool TableRow::setRecord(int idx, String& record)
{
    if(idx >= capacity)
    {
        capacity = 2*idx+1;
        records = (TableRecord**)realloc(records, sizeof(TableRecord*) * capacity);
        for(int i = size; i < capacity; i++)
        {
            records[i] = nullptr;
        }
        size = idx+1;
    }
    if(idx >= size) size = idx+1;
    String tmp1;
    bool result = true;
    tmp1 = record.getData();
    trim(tmp1);
    tmp1.append('\0');
    int type = checkType(tmp1);
    delete records[idx];
    switch(type)
    {
        case TYPE_NUMBER:
        {
            records[idx] = new NumberRecord(tmp1);
            maxRLength = std::max(maxRLength, int(tmp1.Size()));
            break;
        }
        case TYPE_RATIONAL:
        {
            records[idx] = new RationalRecord(tmp1);
            maxRLength = std::max(maxRLength, int(tmp1.Size()));
            break;
        }
        case TYPE_STRING:
        {
            records[idx] = new StringRecord(tmp1);
            maxRLength = std::max(maxRLength, int(tmp1.Size()));
            break;
        }
        case TYPE_FORMULA:
        {
            records[idx] = new FormulaRecord(tmp1);
            maxRLength = std::max(maxRLength, 10);
            break;
        }
        case TYPE_UNDEF:
        {
            result = false;
            std::cout<<"UndefRecord: "<<tmp1<<std::endl;
            break;
        }
    
    }
    return result;
}
TableRow::TableRow(String& row)
{
    String tmp1;
    maxRLength = 0;
    tmp1 = "";
    int itemsC = countItems(row);
    records = new TableRecord*[itemsC];
    int idx = 0;
    row.append(',');
    row.append('\0');
    for(int i = 0; i < row.Size(); i++)
    {
        if(row[i] != ',')
        {
            tmp1.append(row[i]);
        }
        else
        {
            tmp1.append('\0');
            records[idx] = nullptr;
            bool result = setRecord(idx, tmp1);
            if(result) idx++;
            tmp1 = "";
        }
        size = idx;
        capacity = size;
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