#include "App\TopologyMapTab.h"
#include "App\SceneZoom.h"
#include "App\TopologyMapView.h"
#include "App\SearchManager.h"
#include "GraphicView\TopologyMapScene.h"

#include "Panel\InfoPanel.h"
#include "Panel\LegendPanel.h"

using namespace App;

TopologyMapTab::TopologyMapTab(const TopologyMap& map, const std::string& name, QWidget* parent):
    QWidget(parent),
    m_name(name),
    m_topologyMap(map)
{
    m_view = new TopologyMapView(this);

    auto scene = new GV::TopologyMapScene(m_view);
    m_view->setScene(scene);

    m_zoom = std::make_unique<SceneZoom>(m_view);

    m_legend = std::make_unique<Panel::LegendPanel>(m_view);
    m_infoPanel = std::make_unique<Panel::InfoPanel>(m_view);

    m_searchManager = std::make_shared<SearchManager>();
    


    m_zoom->setMechanism(m_topologyMap.getGraphicModel());
    auto topologyMapScene = dynamic_cast<GV::TopologyMapScene*>(m_view->scene());

    topologyMapScene->addElements(m_topologyMap.getGraphicModel());
    topologyMapScene->setInfoPanelRelations(m_infoPanel);
}

std::string App::TopologyMapTab::getName() const
{
    return m_name;
}

TopologyMapView * App::TopologyMapTab::getView() const
{
    return m_view;
}

void App::TopologyMapTab::setTopologyMap(const TopologyMap & map)
{
    m_topologyMap = map;
}

TopologyMap App::TopologyMapTab::getTopologyMap() const
{
    return m_topologyMap;
}

void App::TopologyMapTab::displayLegend(bool checked)
{
    m_legend->display(checked);
}

void App::TopologyMapTab::displayInfoPanel(bool checked)
{
    m_infoPanel->display(checked);
}
