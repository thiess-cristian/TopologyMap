#include "ConnectorStringToEnum.h"

ConnectorStringToEnum::ConnectorStringToEnum()
{
    m_names["Spring"] = ConnectorKind::Spring;
    m_names["Damper"] = ConnectorKind::Damper;
    m_names["Bushing"] = ConnectorKind::Bushing;
    m_names["BeamForce"] = ConnectorKind::BeamForce;
}
