#include "TableRecord.hpp"

class RationalRecord : public TableRecord
{
    public:
        double getRecord();
        int getType() override;
        RationalRecord(String& _data);

};