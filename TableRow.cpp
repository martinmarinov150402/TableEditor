#include <iostream>
#include "TableRow.hpp"
#include "TableRecord.hpp"
#include "checkType.hpp"
#include "NumberRecord.hpp"
#include "RationalRecord.hpp"
#include "StringRecord.hpp"

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
        data = records[i]->getRawData();
        for(int j = 0; j < data.Size(); j++)
        {
            out<<data[j];
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
TableRow::TableRow(String& row)
{
    std::cout<<"VIKAM TEB S "<<row<<std::endl;
    String tmp1;

    tmp1 = "";
    std::cout<<"ITEMSC"<<std::endl;
    int itemsC = countItems(row);
    std::cout<<"itemsC: "<<itemsC<<std::endl;
    records = new TableRecord*[itemsC];
    std::cout<<"HERE";
    int idx = 0;
    row.append(',');
    std::cout<<row.Size()<<std::endl;   
    for(int i = 0; i < row.Size(); i++)
    {
        std::cout<<"I: "<<i<<std::endl;
        if(row[i] != ',')
        {
            tmp1.append(row[i]);
        }
        else
        {
            trim(tmp1);
            int type = checkType(tmp1);
            tmp1.append('\0');
            
            switch(type)
            {
                case TYPE_NUMBER:
                {
                    records[idx++] = new NumberRecord(tmp1);
                    break;
                }
                case TYPE_RATIONAL:
                {
                    records[idx++] = new RationalRecord(tmp1);
                    break;
                }
                case TYPE_STRING:
                {
                    std::cout<<"StringRec:"<<tmp1<<std::endl;
                    records[idx++] = new StringRecord(tmp1);
                    break;
                }
                case TYPE_UNDEF:
                {
                    std::cout<<"First: "<<tmp1[0]<<" Last: "<<tmp1[tmp1.Size()-1]<<std::endl;
                    std::cout<<"UNDEFREC: "<<tmp1<<std::endl;
                    std::cout<<tmp1.Size();
                    break;
                }
            
            }
            tmp1 = "";
            //std::cout<<records[idx-1]->getRawData()<<std::endl;
        }
        size = idx;
        capacity = size;
        std::cout<<"COMP I: "<<i<<std::endl;
    }
    std::cout<<"TUKA";
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