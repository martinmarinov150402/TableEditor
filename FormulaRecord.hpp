#include "TableRecord.hpp"
#include "string.h"
#include "checkType.hpp"

class FormulaRecord : public TableRecord
{
    public:
        int getType() override { return TYPE_FORMULA; };
        FormulaRecord(String _data)
        {
            setData(_data);
        }
};