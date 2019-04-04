#pragma once

#include "DocumentParser.h"
#include "Enums.h"
#include "XMLTagNames.h"
#include <vector>
#include <qobject.h>
#include <map>

class TopologyMapScene;
class GraphicMotionBody;
class GraphicJoint;
class GraphicConnector;
class GraphicMechanism;
class IPerspective;
class InfoPanel;

class ElementsManager:public QObject
{
    Q_OBJECT
public:
    ElementsManager();
    
    void openElements(QFile& file);
    void saveElements(QFile& file, std::string modelName);
    void loadElements(QFile& file, std::string modelName);
    void addElementsToScene(TopologyMapScene * scene);
    void changePerspective(IPerspective* perspective);

    double computeScaleFactor();
    QPointF computeTranslationPoint();
    
    void displayElementName(ElementType type, bool checked);

    std::shared_ptr<Mechanism> getMechanism() const;
    std::shared_ptr<GraphicMechanism> getGraphicMechanism() const;

    void setWindowSize(size_t windowHeight,size_t windowWidth);

    void setUpInfoPanelRelations(std::shared_ptr<InfoPanel> infoPanel);

public slots:
    void applyScale(double scaleFactor);
    void applyTranslation(QPointF translatePoint);

private:
    std::map<std::string, GraphicMotionBody*> createMotionBodies() const;
    std::map<std::string, GraphicJoint*> createJoints() const;
    std::map<std::string, GraphicConnector*> createConnectors() const;

    void changeMotionBodiesPerspective(IPerspective* perspective);
    void changeJointsPerspective(IPerspective* perspective);
    void changeConnectorsPerspective(IPerspective* perspective);

    void setStackingOrder();

    std::shared_ptr<Mechanism> m_mechanism = nullptr;
    std::shared_ptr<GraphicMechanism> m_graphicsMechanism = nullptr;

    double m_scaleFactor;

    size_t m_windowHeight;
    size_t m_windowWidth;
};