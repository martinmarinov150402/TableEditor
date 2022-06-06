#include "NumberRecord.hpp"
#include "checkType.hpp"

class StringRecord: public TableRecord
{
    public:
        int getType() override { return TYPE_STRING; };
        StringRecord(String& _data)
        {
            setData(_data);
        }
};