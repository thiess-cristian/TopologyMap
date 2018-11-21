#include "TopPerspectiveElementsCreator.h"
#include "GraphicMotionBody.h"
#include "GraphicJoint.h"
#include "GraphicConnector.h"


#include "Mechanism.h"

TopPerspectiveElementsCreator::TopPerspectiveElementsCreator(std::shared_ptr<Mechanism> mechanism):m_mechanism(mechanism)
{

}

std::vector<GraphicMotionBody*> TopPerspectiveElementsCreator::createMotionBodies() const
{
    std::vector<GraphicMotionBody*> motionBodies;

    for (const auto& item : m_mechanism->getMotionBodies()) {
        const auto& motionBody= item.second;

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
            if (point.getY() > maxY) {
                maxY = point.getY();
            }
            if (point.getY() < minY) {
                minY = point.getY();
            }
        }

        graphicMotionBody->setBoundingRect(QRectF(minX, minY, maxX - minX, maxY - minY));
        graphicMotionBody->setOrigin(QPoint(motionBody.getX(), motionBody.getY()));
        motionBodies.push_back(graphicMotionBody);
    }

    return motionBodies;
}

std::vector<GraphicJoint*> TopPerspectiveElementsCreator::createJoints() const
{
    std::vector<GraphicJoint*> graphicJoints;

    for (const auto& item : m_mechanism->getJoints()) {
        const auto& joint = item.second;

        GraphicJoint* graphicJoint = new GraphicJoint(joint);

        graphicJoint->setAction(QPoint(joint.getAction().getX(), joint.getAction().getY()));
        graphicJoint->setBase(QPoint(joint.getBase().getX(), joint.getBase().getY()));

        graphicJoints.push_back(graphicJoint);
    }

    return graphicJoints;
}

std::vector<GraphicConnector*> TopPerspectiveElementsCreator::createConnectors() const
{
    std::vector<GraphicConnector*> graphicConnectors;

    for (const auto& item : m_mechanism->getConnectors()) {
        const auto& connector = item.second;

        GraphicConnector* graphicConnector = new GraphicConnector(connector);

        graphicConnector->setAction(QPoint(connector.getAction().getX(), connector.getAction().getY()));
        graphicConnector->setBase(QPoint(connector.getBase().getX(), connector.getBase().getY()));

        graphicConnectors.push_back(graphicConnector);
    }

    return graphicConnectors;
}
