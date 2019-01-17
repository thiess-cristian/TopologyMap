#include "ConnectorStringToEnum.h"

ConnectorStringToEnum::ConnectorStringToEnum()
{
    m_names["Spring"] = ConnectorKind::Spring;
    m_names["Damper"] = ConnectorKind::Damper;
}
