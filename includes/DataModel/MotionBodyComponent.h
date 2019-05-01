#pragma once
#include "DataModel\Element.h"
#include <map>
#include <memory>

namespace DataModel
{
    class MotionBody;

    class MotionBodyComponent:public Element
    {
    public:
        MotionBodyComponent(const std::string& name);
        void addMotionBody(std::shared_ptr<MotionBody> motionBody);


    private:
        std::map<std::string, std::shared_ptr<MotionBody>> m_motionBodies;

    };


}