#include "ConnectorStringToEnum.h"

ConnectorStringToEnum::ConnectorStringToEnum()
{
    m_names["Spring"] = ConnectorName::Spring;
    m_names["Damper"] = ConnectorName::Damper;
}
