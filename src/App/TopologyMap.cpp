#include "App\TopologyMap.h"
#include <DataHandler\DocumentParser.h>
#include <DataHandler\SceneToXML.h>
#include <DataHandler\SceneFromXML.h>

#include <GraphicModel\Mechanism.h>
#include <GraphicModel\Element.h>
#include <DataModel\Mechanism.h>

using namespace App;

TopologyMap::TopologyMap()
{    
}

void TopologyMap::openElements(QFile & file)
{
    DataHandler::DocumentParser parser;
    
    m_dataModelMechansim = parser.parseFile(file);
    
    m_graphicModelMechansim = std::make_shared<GM::Mechanism>(m_dataModelMechansim);
}

void TopologyMap::saveElements(QFile & file, std::string modelName)
{
    DataHandler::SceneToXML sceneWriter(modelName);

    sceneWriter.writeToXml(m_graphicModelMechansim, file);
}

void TopologyMap::loadElements(QFile & file, std::string modelName)
{
    DataHandler::SceneFromXML sceneReader(modelName);

    sceneReader.updateFromXML(m_graphicModelMechansim, file);
}

void App::TopologyMap::displayElementName(DataModel::ElementType type, bool checked)
{    
    auto elementContainer = m_graphicModelMechansim->getElements()[type];
    for (auto& element : elementContainer) {
        element.second->enableDisplayingName(checked);
    }
}

std::shared_ptr<DataModel::Mechanism> TopologyMap::getDataModel() const
{
    return m_dataModelMechansim;
}

std::shared_ptr<GM::Mechanism> TopologyMap::getGraphicModel() const
{
    return m_graphicModelMechansim;
}
