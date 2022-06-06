#include <iostream>

void ag()
{
    freopen("automata.txt","w",stdout);
    for(int i = 0; i < 9; i++)
    {
        std::cout<<"{ ";
        for(char j = 0; j < 127; j++)
        {
            switch(i)
            {
                case 0:
                {
                    std::cout<<"0, ";
                    break;
                }
                case 1:
                {
                    if(j >= '1' && j <= '9')
                    {
                        std::cout<<"3, ";
                    }
                    else if(j == '+' || j == '-')
                    {
                        std::cout<<"2, ";
                    }
                    else if(j == '"')
                    {
                        std::cout<<"5, ";
                    }
                    else
                    {
                        std::cout<<"0, ";
                    }
                    break;
                }
                case 2:
                {
                    if(j >= '1' && j <= '9')
                    {
                        std::cout<<"3, ";
                    }
                    else
                    {
                        std::cout<<"0, ";
                    }
                    break;
                }
                case 3:
                {
                    if(j >= '0' && j <= '9')
                    {
                        std::cout<<"3, ";
                    }
                    else if(j == '.')
                    {
                        std::cout<<"4, ";
                    }
                    else
                    {
                        std::cout<<"0, ";
                    }
                    break;
                }
                case 4:
                {
                    if(j >= '0' && j <= '9')
                    {
                        std::cout<<"8, ";
                    }
                    else
                    {
                        std::cout<<"0, ";
                    }
                    break;
                }
                case 5:
                {
                    if(j == '\\')
                    {
                        std::cout<<"6, ";
                    }
                    else if(j == '"')
                    {
                        std::cout<<"7, ";
                    }
                    else
                    {
                        std::cout<<"5, ";
                    }
                    break;
                }
                case 6:
                {
                    std::cout<<"5, ";
                    break;
                }
                case 7:
                {
                    std::cout<<"0, ";
                    break;
                }
                case 8:
                {
                    if(j >= '0' && j <= '9')
                    {
                        std::cout<<"8, ";
                    }
                    else
                    {
                        std::cout<<"0, ";
                    }
                    break;
                }
            }
            
        }
        std::cout<<"}, \n";
    }
}