#include "Table.hpp"
#include "string.h"
#include "TableRecord.hpp"
#include <fstream>

static int countItems(String tr)
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
    file = "";
    sizeRows = 0;
    capacityRows = 1;
    tableContent = new TableRow*[capacityRows];
}
void Table::addRow(String& row)
{
    if(sizeRows == capacityRows)
    {
        std::cout<<"TI EBA MAIKATA TI EBA\n";
        capacityRows *= 2; 
        TableRow** tmp = tableContent;
        tableContent = new TableRow*[capacityRows];
        for(int i = 0; i < sizeRows; i++)
        {
            tableContent[i] = tmp[i];
            tmp[i] = nullptr;
        }
        delete[] tmp;
    }
    std::cout<<"BUGCHECK\n";
    std::cout<<sizeRows<<std::endl;
    tableContent[sizeRows++] = new TableRow(row);
    std::cout<<"SUCCESS\n";
}
Table::Table(String fileName)
{
    file = fileName;
    sizeRows = 0;
    capacityRows = 1;
    std::ifstream tableInput;
    tableInput.open(fileName.getData());
    String line; 
    tableContent = new TableRow*[capacityRows];
    if(tableInput)
    {
        while(tableInput.eofbit)
        {
            line.readLine(tableInput);
            if(line == "#")break;
            int items = countItems(line);
            addRow(line);
            
            /*for(int i = 0; i < items; i++)tableContent[idx][i] = nullptr;*/
        }
    }
    tableInput.close();
}
Table::~Table()
{
    delete[] tableContent;
}
void Table::copy(Table const& other)
{
    sizeRows = other.sizeRows;
    capacityRows = other.capacityRows;
    if(capacityRows)
    {
        tableContent = new TableRow*[capacityRows];
        for(int i = 0; i < sizeRows; i++)
        {
            tableContent[i] = other.tableContent[i];
        }
    }

}
bool Table::save()
{
    std::ofstream fout;
    fout.open(file.getData());
    if(fout)
    {
        for(int i = 0; i < sizeRows; i++)
        {
            tableContent[i]->WriteOnStream(std::cout);
            tableContent[i]->WriteOnStream(fout);
        }
        fout << "#";
        fout.close();
        return true;
    }
    return false;
}
bool Table::saveAs(String& _file)
{
    file = _file;
    return save();
}