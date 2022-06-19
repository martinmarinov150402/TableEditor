#ifndef DEF_STR
#define DEF_STR

#include <iostream>

class String
{
    private:
        char* data;
        size_t size;
        size_t capacity;
        void copy(String& other);

    public:
        String();
        String& operator=(String& other);
        String& operator=(char* other);
        String& operator=(const char other[]);
        bool hasSubstring(String const& other);
        bool readFromFile(std::ifstream& in);
        void writeInFile(std::ofstream& out);
        char& operator[](size_t idx);
        String(String& other);
        String(char* other);
        ~String();
        size_t Size();
        void append(char* other);
        void append(char other);
        void append(String& other);
        bool operator==(String& other);
        bool operator==(const char*);
        bool operator>(String other);
        const char* getData();
        void readLine(std::istream& in);
        void readTillEOF(std::istream& in);
        void termRem();
    
    friend std::ostream& operator<<(std::ostream& out, String const& str);
    friend std::istream& operator>>(std::istream& in, String& str);
};
#endif