#include <iostream>
#include "string.h"
#include "Table.hpp"
#include "checkType.hpp"
#include "automataGen.cpp"
#include "math.cpp"

int main()
{
    /*String express;
    express = "10+ 30";
    std::cout<<calculateExpression(express);*/
    String asd;
    asd = "testTable.txt";
    Table a(asd);
    a.printTable();
    String sas;
    sas = "testSaveAs.txt";
    a.saveAs(sas);
    
    
}