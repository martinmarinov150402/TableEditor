#ifndef NUMBER_RECORD
#define NUMBER_RECORD

#include "TableRecord.hpp"

class NumberRecord : public TableRecord
{
    public:
        int getRecord();
        NumberRecord(String _data)
        {
            setData(_data);
        }
        int getType() override;
};

#endif