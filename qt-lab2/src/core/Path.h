#pragma once
#include <QPointF>
#include <QVector>

class Path {
public:
    Path();
    
    void addPoint(const QPointF& point);
    void clear();
    const QVector<QPointF>& getPoints() const;
    float getTotalLength() const;
    
    float getDistanceAtPoint(const QPointF& point) const;
    QPointF getPointAtDistance(float distance) const;
    
private:
    struct ProjectionResult {
        float startDistance;     // start到投影点的距离
        float pointDistance;     // point到投影点的距离
    };

    QVector<QPointF> points;
    ProjectionResult findClosestPointOnSegment(const QPointF& point, const QPointF& start, const QPointF& end) const;
    float calculateSegmentLength(const QPointF& start, const QPointF& end) const;
};