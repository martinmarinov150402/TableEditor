#include "RationalRecord.hpp"
#include <cstring>
#include "checkType.hpp"

int RationalRecord::getType()
{
    return TYPE_RATIONAL;
}
double RationalRecord::getRecord()
{
    return atof(getRawData());
}
RationalRecord::RationalRecord(String& _data)
{
    setData(_data);
}