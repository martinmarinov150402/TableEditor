#include "Table.hpp"
#include "TableRecord.hpp"

Table::Table()
{
    sizeRows = 0;
    sizeCols = 0;
    capacityRows = capacityCols = DEFAULT_T_CAPACITY;
    for(int i = 0; i < capacityRows; i++)
    {
        tableContent[i] = new TableRecord[capacityCols];
    }
}