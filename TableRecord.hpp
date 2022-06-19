#ifndef TABLE_REC_DEF
#define TABLE_REC_DEF

#include "string.h"

class TableRecord
{
    private:
        String data;

    protected:

    public:
        virtual int getType() = 0;
        const char* getRawData() { return data.getData(); };
        String getStringRawData() { return data; }; 
        void setData(String _data) {data = _data; };
        double calculateFormula();

};

#endif