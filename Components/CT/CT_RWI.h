#ifndef CT_WI_H 
#define CT_WI_H
#include "Common.h"

typedef enum Vars_enum{
    PointDirectionX,
    PointDirectionY,
    PositionLastWriterID,
    VARS_ENUM_SIZE
}Vars_enum;

#define Type_PointDirectionX sint8
void Write_PointDirectionX(Type_PointDirectionX);
Type_PointDirectionX Read_PointDirectionX();

#define Type_PointDirectionY sint8
void Write_PointDirectionY(Type_PointDirectionY);
Type_PointDirectionY Read_PointDirectionY();

#define Type_PositionLastWriterID uint8
void Write_PositionLastWriterID(Type_PositionLastWriterID);
Type_PositionLastWriterID Read_PositionLastWriterID();

#endif