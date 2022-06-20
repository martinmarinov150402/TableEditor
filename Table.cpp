#include "Table.hpp"
#include "string.h"
#include "TableRecord.hpp"
#include <fstream>
#include "checkType.hpp"
#include <sstream>
#include "math.cpp"
#include <iomanip>

double Table::calculateFormula(int _row, int _col)
{
    if(tableContent[_row]->operator[](_col) -> getType() != TYPE_FORMULA)
    {
        if(tableContent[_row]->operator[](_col) -> getType() == TYPE_STRING || tableContent[_row]->operator[](_col) -> getType() == TYPE_UNDEF )
        {
            return 0;
        }
        else
        {
            return atof(tableContent[_row]->operator[](_col) -> getRawData());
        }
    }
    String data;
    data = tableContent[_row]->operator[](_col)->getRawData();
    data.append('\0');
    String expression;
    expression = "";
    bool startedAddress = false;
    bool colS = false;
    String row;
    String col;
    row="";
    col="";
    for(int i = 1; i < data.Size(); i++)
    {
        if(!startedAddress)
        {
            if(data[i] == 'R')
            {
                startedAddress = true;
            }
            else
            {
                expression.append(data[i]);
                expression.append('\0');
            }
        }
        else
        {
            if(data[i] == 'C')
            {
                colS = true;
            }
            else if(data[i] == ' ')
            {
                if(startedAddress && colS)
                {

                    colS = false;
                    startedAddress = false;
                    String result;
                    std::ostringstream sstr;
                    sstr<<calculateFormula(atoi(row.getData()),atoi(col.getData()));
                    result = sstr.str().c_str();
                    expression.append(result);
                    expression.append('\0');
                    row="";
                    col="";
                }

            }
            else
            {
                if(colS)
                {
                    col.append(data[i]);
                }
                else
                {
                    row.append(data[i]);
                }
            }
        }
    }
    expression.append('\0');
    //std::cout<<"BeforeLast: " <<expression<<" \n\n";
    if(startedAddress && colS)
    {

        colS = false;
        startedAddress = false;
        String result;
        std::ostringstream sstr;
        sstr<<calculateFormula(atoi(row.getData()),atoi(col.getData()));
        result = sstr.str().c_str();
        expression.append(result);
        row="";
        col="";
    }
    expression.append('\0');
    return calculateExpression(expression);
}

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
    tableContent[sizeRows++] = new TableRow(row);
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
        std::cout<<"Successfully opened file "<<fileName<<std::endl;
        tableInput.close();
    }
    else
    {
        std::cout<<"Error with opening of file "<<fileName;
    }
}
bool Table::setRecord(int _row, int _col, String& record)
{
    if(_row > sizeRows)
    {
        for(int i = sizeRows; i <= _row; i++)
        {
            String es;
            es = "";
            addRow(es);
        }

    }
    return tableContent[_row]->setRecord(_col, record);
}
Table::~Table()
{

    for(int i = 0; i < sizeRows; i++)
    {
        delete tableContent[i];
    }
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
            tableContent[i]->WriteOnStream(fout);
        }
        fout << "#\n";
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
void Table::printTable()
{
    for(int i = 0; i < sizeRows; i++)
    {
        maxRLength = std::max(maxRLength, tableContent[i]->getMaxRLength());
        maxCLength = std::max(maxCLength, tableContent[i]->getSize());
    }
    for(int j = 0; j < maxCLength*(maxRLength+3); j++)
    {
        std::cout<<"-";
    }
    std::cout<<std::endl;
    for(int i = 0; i < sizeRows; i++)
    {
        for(int j = 0; j < tableContent[i]->getSize(); j++)
        {
            if(tableContent[i]->operator[](j) != nullptr)
            {
                if(tableContent[i]->operator[](j)->getType() == TYPE_FORMULA)
                {
                    std::cout<<std::setw(maxRLength)<<calculateFormula(i,j)<<" | ";
                }
                else
                {
                    std::cout<<std::setw(maxRLength)<<tableContent[i]->operator[](j)->getRawData() <<" | ";
                } 
            }
            else
            {
                std::cout<<std::setw(maxRLength)<<" | ";
            }
            
        }
        for(int j = tableContent[i]->getSize(); j < maxCLength; j++)
        {
            std::cout<<std::setw(maxRLength)<<""<<" | ";
        }
        std::cout<<std::endl;
        for(int j = 0; j < maxCLength*(maxRLength+3); j++)
        {
            std::cout<<"-";
        }
        std::cout<<std::endl;
    }
}