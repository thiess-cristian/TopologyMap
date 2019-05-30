#pragma once
#include <qtabwidget.h>
#include <memory>
#include <string>
#include <TopologyMap.h>

namespace Panel
{
    class InfoPanel;
    class LegendPanel;
}


namespace App
{
    class SceneZoom;
    class SearchWindow;
    class SearchManager;
    class TopologyMapView;

    class TopologyMapTab:public QWidget
    {
    public:
        TopologyMapTab(const TopologyMap& map,const std::string& name,QWidget* parent = nullptr);

        std::string getName()const;
        TopologyMapView* getView() const;

        void setTopologyMap(const TopologyMap& map);
        TopologyMap getTopologyMap()const;

        void displayLegend(bool checked);
        void displayInfoPanel(bool checked);

    private:

        std::string m_name;

        TopologyMapView* m_view;
        TopologyMap m_topologyMap;

        std::shared_ptr<SearchManager> m_searchManager;
        std::unique_ptr<SceneZoom> m_zoom;
        std::unique_ptr<Panel::LegendPanel> m_legend;
        std::shared_ptr<Panel::InfoPanel> m_infoPanel;
    };


}