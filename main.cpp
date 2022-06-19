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
    String command;
    command = "";
    Table *a = nullptr;
    while(true)
    {
        std::cin>>command;
        if(command == "exit")
        {
            if(a != nullptr)
            {
                std::cout<<"Има отворена таблица първо я затворете\n";
            }
            else
            {
                std::cout<<"Довиждане!\n";
                break;
            }
            
        }
        if(command == "open")
        {
            if(a == nullptr)
            {
                String fileName;
                std::cout<<"Въведете име на файла:"<<std::endl;
                std::cin>>fileName;
                a = new Table(fileName);
            }
            else
            {
                std::cout<<"Има отворена таблица!\n";
            }
        }
        if(command == "close")
        {
            if(a != nullptr)
            {
                delete a;
                a = nullptr;
                std::cout<<"Таблицата е затворена успешно!\n";
            }
            else
            {
                std::cout<<"Няма отворена таблица\n";
            }
        }
        if(command == "save")
        {
            if(a != nullptr)
            {
                if(a->save())
                {
                    std::cout<<"Table was saved successfully\n";
                }
                else
                {
                    std::cout<<"Error with saving the table\n";
                }
            }
            else
            {
                std::cout<<"There isn't opened table\n";
            }
            
        }
        if(command == "saveas")
        {
            if(a != nullptr)
            {
                String fileName;
                std::cout<<"Въведете име на файла в който да се запише таблицата:"<<std::endl;
                std::cin>>fileName;
                if(a->saveAs(fileName))
                {
                    std::cout<<"Table was saved successfully in "<<fileName<<std::endl;
                }
            }
            else
            {
                std::cout<<"There isn't opened table\n";
            }

        }
        if(command == "help")
        {
            std::cout<< "open - Отваря файл\n"
                     << "close - Затваря отворения файл. Внимание не записва промените за да запишете първо save\n"
                     << "save - Записва промените\n"
                     << "saveas - Записва промените в друг файл\n"
                     << "help - Отваря списък с командите\n"
                     << "exit - Затваря програмата\n"
                     << "edit - Променя дадена клетка\n"
                     << "print - Извежда таблицата\n";
        }
        if(command == "print")
        {
            if(a != nullptr)
            {
                a->printTable();
            }
            else
            {
                std::cout<<"Няма отворена таблица!\n";
            }
        }
        if(command == "edit")
        {
            if(a != nullptr)
            {
                String r;
                String c;
                int row;
                int col;
                String record;
                std::cout<<"Въведете ред (започва от 0): \n";
                r.readLine(std::cin);
                row = atoi(r.getData());
                std::cout<<"Въведете колона (започва от 0): \n";
                c.readLine(std::cin);
                col = atoi(c.getData());
                std::cout<<"Въведете нова стойност: \n";
                record.readLine(std::cin);
                a->setRecord(row,col,record);
            }
            else
            {
                std::cout<<"Няма отворена таблица!\n";
            }
            

        }

    }
    
    
}