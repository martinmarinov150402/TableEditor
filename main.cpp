#include <iostream>
#include "string.h"
#include "Table.hpp"
#include "checkType.hpp"

int main()
{
    int matrix[3][4] = {
        {1,2,3,4,},
        {5,6,7,8,},
        {9,10,11,12,},
    };
    String asd;
    asd = "testTable.txt";
    Table a(asd);
    String sas;
    sas = "testSaveAs.txt";
    a.saveAs(sas);
    
    
}