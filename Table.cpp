#include "Table.hpp"
#include "string.h"
#include "TableRecord.hpp"
#include <fstream>

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
Table::Table()
{
    sizeRows = 0;
    capacityRows = DEFAULT_T_CAPACITY;
    tableContent = nullptr;
}
Table::Table(String fileName)
{
    std::ifstream tableInput;
    tableInput.open(fileName.getData());
    String line; 
    int idx = 0;
    tableContent = nullptr;
    if(tableInput)
    {
        while(tableInput.eofbit)
        {
            line.readLine(tableInput);
            if(line == "#")break;
            int items = countItems(line);
            
            /*tableContent[idx] = new TableRecord*[items];
            for(int i = 0; i < items; i++)tableContent[idx][i] = nullptr;*/
            std::cout<<line<<std::endl;
        }
    }
    tableInput.close();
    std::cout<<"Suka"<<std::endl;
}
Table::~Table()
{
    std::cout<<"TUKA";
    delete[] tableContent;
}
void Table::copy(Table const& other)
{
    sizeRows = other.sizeRows;
    capacityRows = other.capacityRows;
    if(capacityRows)
    {
        tableContent = new TableRow[capacityRows];
        for(int i = 0; i < sizeRows; i++)
        {
            tableContent[i] = other.tableContent[i];
        }
    }

}