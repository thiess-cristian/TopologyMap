#pragma once
#include "XMLTagNames.h"
#include "IElementStringToEnum.h"


class JointStringToEnum :public IElementStringToEnum<JointType>
{
public:
    JointStringToEnum(); 
};
