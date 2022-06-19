#include "string.h"
#include <cstring>
#include <limits>
#include <fstream>
#include <curses.h>

const size_t DEFAULT_CAPACITY = 10;
String::~String()
{
    delete[] data;
}
String::String()
{
    capacity = DEFAULT_CAPACITY;
    size = 0;
    data = new char[capacity];
    data[0] = '\0';
}
void String::copy(String& other)
{
    size = other.size;
    capacity = other.capacity;
    data = new char[capacity];
    strcpy(data,other.data);
}
String::String(String& other)
{
    size = other.size;
    capacity = other.capacity;
    data = new char[capacity];
    strcpy(data,other.data);
}
String& String::operator=(String& other)
{
    if(this != &other)
    {
        delete[] data;
        copy(other);
    }
    return *this;
}
void String::termRem()
{
    if(data[size-1]=='\0')
    {
        size--;
    }
}
String& String::operator=(char* other)
{
    size = strlen(other);
    capacity = size+1;
    delete[] data;
    data = new char[capacity];
    strcpy(data,other);
    return *this;
}
String& String::operator=(const char* other)
{
    size = strlen(other);
    capacity = size+1;
    delete[] data;
    data = new char[capacity];
    strcpy(data,other);
    return *this;
}
bool String::hasSubstring(String const& other)
{
    return (strstr(data, other.data) != nullptr);
}
bool String::operator>(String other)
{
    bool flag = true;
    int bound = std::min(other.size, size);
    for(int i = 0; i < bound; i++)
    {
        if(data[i] < other.data[i])
        {
            flag = false;
            break;
        }
    }
    return flag;
}
bool String::readFromFile(std::ifstream& in)
{
    if(!in)
    {
        return false;
    }
    size = 0;
    capacity = DEFAULT_CAPACITY;
    delete[] data;
    data = new char[capacity];
    char sym=' ';
    bool flag = true;
    while(sym != '\0' && flag)
    {
        
        flag = flag && in.read(&sym,sizeof(sym));
        //if(sym != '\0')
        //{
            if(size + 1 > capacity)
            {
                char *tmp = data;
                capacity *= 2;
                data = new char[capacity];
                strcpy(data,tmp);
            }
            data[size++] = sym;
        //}

        
    }
    size--;
    return flag;
}
char& String::operator[](size_t idx)
{
    return data[idx];
}
void String::writeInFile(std::ofstream& out)
{
    if(!out)
    {
        return;
    }
    out.write(data,size);
    char term0 = '\0';
    out.write(&term0, sizeof(char));
}
String::String(char* other)
{
    *this = other;
}
size_t String::Size()
{
    return size;
}
void String::append(char* other)
{
    if(capacity < size + strlen(other))
    {
        capacity = capacity + strlen(other);
        char *tmp = data;
        data = new char[capacity];
        strcpy(data,tmp);
        delete[] tmp;
    }
    size = size + strlen(other);
    strcat(data,other);   
}
void String::append(char other)
{
    if(capacity == size)
    {
        capacity = capacity * 2;
        char *tmp = data;
        data = new char[capacity];
        strcpy(data,tmp);
        delete[] tmp;
    }
    data[size++] = other;
    if(other == '\0')size--;
}
void String::append(String& other)
{
    append(other.data);
}
std::ostream& operator<<(std::ostream& out, String const& str)
{
    out<<str.data;
    return out;
}
std::istream& operator>>(std::istream& in, String& str)
{
    str.capacity = DEFAULT_CAPACITY;
    str.size = 0;
    delete[] str.data;
    str.data = new char[str.capacity];
    char sym=' ';
    do
    {
        in.get(sym);
        if(sym!= '\n' && sym != ' ')
        {
            if(str.size == str.capacity)
            {
                char* tmp = str.data;
                str.capacity = str.capacity * 2;
                str.data = new char[str.capacity];
                strcpy(str.data,tmp);
                delete[] tmp;
            }
            str.data[str.size++] = sym;
        }
    } 
    while(sym != '\n' && sym != ' ');
    return in;
    
}
void String::readLine(std::istream& in)
{
    capacity = DEFAULT_CAPACITY;
    size = 0;
    delete[] data;
    data = new char[capacity];
    char sym=' ';
    do
    {
        in.get(sym);
        if(sym!= '\n' && sym >=' ' && sym <= '~')
        {
            if(size == capacity)
            {
                char* tmp = data;
                capacity = capacity * 2;
                data = new char[capacity];
                strcpy(data,tmp);
                delete[] tmp;
            }
            data[size++] = sym;
        }
    } 
    while(sym != '\n');
    if(size == capacity)
    {
        char* tmp = data;
        capacity = capacity * 2;
        data = new char[capacity];
        strcpy(data,tmp);
        delete[] tmp;
    }
    data[size] = '\0';
}
void String::readTillEOF(std::istream& in)
{
    capacity = DEFAULT_CAPACITY;
    size = 0;
    delete[] data;
    data = new char[capacity];
    char sym=' ';
    while(in>>sym)
    {
        if(size == capacity)
        {
            char* tmp = data;
            capacity = capacity * 2;
            data = new char[capacity];
            strcpy(data,tmp);
            delete[] tmp;
        }
        data[size++] = sym;
    }
    in.ignore();
    in.clear(); 
}
bool String::operator==(String& other)
{
    bool flag = true;
    if(size == other.size)
    {
        for(int i = 0; i < size && flag; i++)
        {
            if(data[i] != other.data[i])
            {
                flag = false;
            }
        }
    }
    else
    {
        flag = false;
    }
    return flag;
}
bool String::operator==(const char* other)
{
    bool flag = true;
    if(size == strlen(other))
    {
        for(int i = 0; i < size && flag; i++)
        {
            if(data[i] != other[i])
            {
                flag = false;
            }
        }
    }
    else
    {
        flag = false;
    }
    return flag;
}
const char* String::getData()
{
    return data;
}
