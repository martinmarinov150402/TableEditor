#ifndef TABLE_REC_DEF
#define TABLE_REC_DEF

#include "string.h"

class TableRecord
{
    private:
        String data;

    protected:
        const char* getRawData() { return data.getData(); };
        void setData(String _data) {data = _data; };

    public:
        virtual int getType() = 0;
         

};

#endif