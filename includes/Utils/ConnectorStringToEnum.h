#pragma once
#include "IElementStringToEnum.h"
#include "XMLTagNames.h"

class ConnectorStringToEnum :public IElementStringToEnum<ConnectorKind>
{
public:
    ConnectorStringToEnum();
};