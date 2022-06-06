#include "NumberRecord.hpp"
#include "checkType.hpp"

int NumberRecord::getRecord()
{
    return atoi(getRawData());
}
int NumberRecord::getType()
{
    return TYPE_NUMBER;
}