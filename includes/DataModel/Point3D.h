#pragma once
namespace DataModel
{
    class Point3D
    {
    public:
        Point3D(double x = 0.0, double y = 0.0, double z = 0.0);

        double getX() const;
        double getY() const;
        double getZ() const;

        void setX(double value);
        void setY(double value);
        void setZ(double value);

        bool operator==(const Point3D& point)const;

    private:
        double m_x;
        double m_y;
        double m_z;
    };
}