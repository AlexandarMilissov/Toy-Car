#include "CT.h"
#include "CT_RWI.h"
#include "Common.h"
#include "stdint.h"

void Write_PointDirectionX(Type_PointDirectionX value)
{
    WriteVar(PointDirectionX, (void*)(uintptr_t)value);
}
Type_PointDirectionX Read_PointDirectionX()
{
    return (Type_PointDirectionX)(uintptr_t)ReadVar(PointDirectionX);
}

void Write_PointDirectionY(Type_PointDirectionY value)
{
    WriteVar(PointDirectionY, (void*)(uintptr_t)value);
}
Type_PointDirectionY Read_PointDirectionY()
{
    return (Type_PointDirectionY)(uintptr_t)ReadVar(PointDirectionY);
}

void Write_PositionLastWriterID(Type_PositionLastWriterID value)
{
    WriteVar(PositionLastWriterID, (void*)(uintptr_t)value);
}
Type_PositionLastWriterID Read_PositionLastWriterID()
{
    return (Type_PositionLastWriterID)(uintptr_t)ReadVar(PositionLastWriterID);
}