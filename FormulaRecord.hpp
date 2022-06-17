#include "TableRecord.hpp"
#include "checkType.hpp"

class FormulaRecord : public TableRecord
{
    public:
        int getType() override { return TYPE_FORMULA; };
};