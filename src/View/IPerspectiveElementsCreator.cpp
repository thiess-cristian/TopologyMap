#include "IPerspectiveElementsCreator.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"
#include "Mechanism.h"

std::vector<GraphicMotionBody*> IPerspectiveElementsCreator::createMotionBodies() const
{
    std::vector<GraphicMotionBody*> motionBodies;

    for (const auto& item : m_mechanism->getMotionBodies()) {
        const auto& motionBody = item.second;

        GraphicMotionBody* graphicMotionBody = new GraphicMotionBody(motionBody);

        double minX = DBL_MAX;
        double maxX = -DBL_MAX;
        double minY = DBL_MAX;
        double maxY = -DBL_MAX;
        auto connections = motionBody.getConnectionPoints();
        connections.push_back(motionBody.getOrigin());

        for (const auto& point : connections) {

            QPoint projectedPoint=projectPoint(point);

            if (projectedPoint.x() > maxX) {
                maxX = projectedPoint.x();
            }
            if (projectedPoint.x() < minX) {
                minX = projectedPoint.x();
            }
            if (projectedPoint.y() > maxY) {
                maxY = projectedPoint.y();
            }
            if (projectedPoint.y() < minY) {
                minY = projectedPoint.y();
            }
        }
        QPoint origin = projectPoint(motionBody.getOrigin());

        double mirrorMaxX = 2 * origin.x() -  maxX;
        double mirrorMaxY = 2 * origin.y() -  maxY;

        double mirrorMinX = 2 * origin.x() -  minX;
        double mirrorMinY = 2 * origin.y() -  minY;

        if (mirrorMaxX < minX) {
            minX = mirrorMaxX;
        }

        if (mirrorMaxY < minY) {
            minY = mirrorMaxY;
        }

        if (mirrorMinX > maxX) {
            maxX = mirrorMinX;
        }

        if (mirrorMinY > maxY) {
            maxY = mirrorMinY;
        }

        graphicMotionBody->setBoundingRect(QRectF(minX, minY, maxX - minX, maxY - minY));
        graphicMotionBody->setOrigin(origin);
        graphicMotionBody->setFlag(QGraphicsItem::ItemIsMovable);
        motionBodies.push_back(graphicMotionBody);
    }

    return motionBodies;
}

std::vector<GraphicJoint*> IPerspectiveElementsCreator::createJoints() const
{
    std::vector<GraphicJoint*> graphicJoints;

    for (const auto& item : m_mechanism->getJoints()) {
        const auto& joint = item.second;

        GraphicJoint* graphicJoint = new GraphicJoint(joint);

        QPoint actionConnection = projectPoint(joint.getActionConnection());
        graphicJoint->setAction(actionConnection);
        QPoint baseConnection = projectPoint(joint.getBaseConnection());
        graphicJoint->setBase(baseConnection);

        graphicJoints.push_back(graphicJoint);
    }

    return graphicJoints;
}

std::vector<GraphicConnector*> IPerspectiveElementsCreator::createConnectors() const
{
    std::vector<GraphicConnector*> graphicConnectors;

    for (const auto& item : m_mechanism->getConnectors()) {
        const auto& connector = item.second;

        GraphicConnector* graphicConnector = new GraphicConnector(connector);

        QPoint actionConnection = projectPoint(connector.getActionConnection());
        graphicConnector->setAction(actionConnection);
        QPoint baseConnection = projectPoint(connector.getBaseConnection());
        graphicConnector->setBase(baseConnection);

        graphicConnectors.push_back(graphicConnector);
    }

    return graphicConnectors;
}
