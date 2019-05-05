#pragma once
#include "GraphicView\IElementPainter.h"
#include <memory>

namespace GM
{
    class Connector;
}

namespace GV
{
    class ConnectorPainter :public IElementPainter
    {
    public:
        ConnectorPainter(std::shared_ptr<GM::Connector> connectorModel);
        // Inherited via IElementPainter
        virtual void paintItem(QPainter * painter) const override;
    private:
        std::shared_ptr<GM::Connector> m_connectorModel;
    };



}