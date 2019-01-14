#pragma once
#include "IElementStringToEnum.h"
#include "XMLTagNames.h"

class ConnectorStringToEnum :public IElementStringToEnum<ConnectorName>
{
public:
    ConnectorStringToEnum();
};