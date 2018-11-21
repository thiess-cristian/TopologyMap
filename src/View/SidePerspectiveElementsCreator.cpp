#include "SidePerspectiveElementsCreator.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"
#include "Mechanism.h"

SidePerspectiveElementsCreator::SidePerspectiveElementsCreator(std::shared_ptr<Mechanism> mechanism):m_mechanism(mechanism)
{

}

std::vector<GraphicMotionBody*> SidePerspectiveElementsCreator::createMotionBodies() const
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
            if (point.getX() > maxX) {
                maxX = point.getX();
            }
            if (point.getX() < minX) {
                minX = point.getX();
            }
            if (point.getZ() > maxY) {
                maxY = point.getZ();
            }
            if (point.getZ() < minY) {
                minY = point.getZ();
            }
        }
        graphicMotionBody->setBoundingRect(QRectF(minX, minY, maxX - minX, maxY - minY));
        graphicMotionBody->setOrigin(QPoint(motionBody.getX(), motionBody.getZ()));
        motionBodies.push_back(graphicMotionBody);
    }

    return motionBodies;
}

std::vector<GraphicJoint*> SidePerspectiveElementsCreator::createJoints() const
{
    std::vector<GraphicJoint*> graphicJoints;

    for (const auto& item : m_mechanism->getJoints()) {
        const auto& joint = item.second;

        GraphicJoint* graphicJoint = new GraphicJoint(joint);

        graphicJoint->setAction(QPoint(joint.getAction().getX(), joint.getAction().getZ()));
        graphicJoint->setBase(QPoint(joint.getBase().getX(), joint.getBase().getZ()));

        graphicJoints.push_back(graphicJoint);
    }

    return graphicJoints;
}

std::vector<GraphicConnector*> SidePerspectiveElementsCreator::createConnectors() const
{
    std::vector<GraphicConnector*> graphicConnectors;

    for (const auto& item : m_mechanism->getConnectors()) {
        const auto& connector = item.second;

        GraphicConnector* graphicConnector = new GraphicConnector(connector);

        graphicConnector->setAction(QPoint(connector.getAction().getX(), connector.getAction().getZ()));
        graphicConnector->setBase(QPoint(connector.getBase().getX(), connector.getBase().getZ()));

        graphicConnectors.push_back(graphicConnector);
    }

    return graphicConnectors;
}
