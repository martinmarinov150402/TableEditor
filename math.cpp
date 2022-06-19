#include "string.h"
#include <stack>

static double fpow(double a, int b)
{
    //std::cout<<"A: "<<a<<" "<<"B: "<<b<<std::endl;
    if(b == 0) return 1;
    if(b == 1) return a;
    if(b < 0) return fpow(1/a, -b);
    if(b % 2 == 0) return fpow(a*a, b/2);
    else return a * fpow(a*a, b/2);

}
static bool isNumber(char i)
{
    if(i >= '0' && i <= '9')
    {
        return true;
    }
    return false;
}
static bool isLeftRightAssoc(char op)
{
    if(op == '+' || op == '-' || op == '*' || op == '/') return true;
    return false;
}
static int assignPriority(char a)
{
    if(a == '+' || a == '-') return 1;
    else if(a == '*' || a == '/') return 2;
    else if(a == '^') return 3;
    else return 4;
}
static bool checkPriority(char a, char b)
{
    return assignPriority(a) > assignPriority(b);
}
static bool checkEqualPriority(char a, char b)
{
    return assignPriority(a) == assignPriority(b);
}
static String convertToRPN(String expression)
{
    String result;
    result = "";
    std::stack<char> s;
    for(int i = 0; i < expression.Size(); i++)
    {
        if(isNumber(expression[i]))
        {
            result.append(expression[i]);
        }
        else
        {
            if(expression[i] == ' ')continue;
            result.append(' ');
            if(expression[i] != ')')
            {
                while(!s.empty() && s.top() != '(' && checkPriority(s.top(), expression[i]))
                {
                    result.append(s.top());
                    s.pop();
                }
                while(!s.empty() && checkEqualPriority(s.top(),expression[i]) && isLeftRightAssoc(expression[i]))
                {
                    result.append(s.top());
                    s.pop();
                }
                s.push(expression[i]);
            }
            else
            {
                while(s.top() != '(')
                {
                    result.append(s.top());
                    s.pop();
                }
                s.pop();
            }
        }
    }
    while(!s.empty())
    {
        result.append(s.top());
        s.pop();
    }
    return result;
}
static double calculateRPN(String rpnExpression)
{
    String tmpHolder;
    tmpHolder = "";
    std::stack<double> cont;
    bool forPush = false;
    for(int i = 0; i < rpnExpression.Size(); i++)
    {
        if(isNumber(rpnExpression[i]))
        {
            tmpHolder.append(rpnExpression[i]);
            forPush = true;
        }
        else
        {  
            if(forPush)
            {
                double tmp = atof(tmpHolder.getData());
                tmpHolder = "";
                cont.push(tmp);
                forPush = false;
            }
            if(rpnExpression[i] != ' ')
            {
                
                double second = cont.top();
                cont.pop();
                double first = cont.top();
                cont.pop();
                switch(rpnExpression[i])
                {
                    case '+':
                    {
                        cont.push(first + second);
                        break;
                    }
                    case '-':
                    {  
                        cont.push(first - second);
                        break;
                    }
                    case '*':
                    {
                        cont.push(first * second);
                        break;
                    }
                    case '/':
                    {
                        if(second == 0)
                        {
                            std::cerr<<"Devision with 0 in formula! Assigning 0!";
                            return 0;
                        }
                        cont.push(first / second);
                        break;
                    }
                    case '^':
                    {
                        cont.push(fpow(first,second));
                        break;
                    }
                }
            }
        }
    }
    return cont.top();
}
static double calculateExpression(String expression)
{
    String rpn;
    rpn = convertToRPN(expression).getData();
    return calculateRPN(rpn);
}