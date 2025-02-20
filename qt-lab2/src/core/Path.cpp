#include "Path.h"

#include "Parameter.h"
#include <cmath>

Path::Path() {}

void Path::addPoint(const QPointF& point) {
    points.append(point);
}

void Path::clear() {
    points.clear();
}

const QVector<QPointF>& Path::getPoints() const {
    return points;
}

float Path::getTotalLength() const {
    float length = 0;
    for (int i = 0; i < points.size() - 1; ++i) {
        length += calculateSegmentLength(points[i], points[i + 1]);
    }
    return length;
}

float Path::getDistanceAtPoint(const QPointF& point) const {
    if (points.size() < 2) return 0;
    
    float totalDistance = 0;
    float minDistance = std::numeric_limits<float>::max();
    float resultDistance = 0;
    
    // 遍历所有线段找到最近的点
    for (int i = 0; i < points.size() - 1; ++i) {
        ProjectionResult result = findClosestPointOnSegment(point, points[i], points[i + 1]);
        if (result.pointDistance < minDistance) {
            minDistance = result.pointDistance;
            resultDistance = totalDistance + result.startDistance;
        }
        totalDistance += calculateSegmentLength(points[i], points[i + 1]);
    }
    
    return resultDistance;
}

QPointF Path::getPointAtDistance(float distance) const {
    if (points.size() < 2) return QPointF(); // 如果路径没有足够的点，返回空点
    if (distance <= 0) return points.first();
    
    float currentDistance = 0;
    
    // 遍历所有线段找到目标距离所在的线段
    for (int i = 0; i < points.size() - 1; ++i) {
        float segmentLength = calculateSegmentLength(points[i], points[i + 1]);
        if (currentDistance + segmentLength >= distance) {
            // 计算在当前线段上的具体位置
            float t = (distance - currentDistance) / segmentLength;
            return points[i] + (points[i + 1] - points[i]) * t;
        }
        currentDistance += segmentLength;
    }
    
    return points.last();
}

Path::ProjectionResult Path::findClosestPointOnSegment(const QPointF& point, const QPointF& start, const QPointF& end) const {
    QPointF segment = end - start;
    float segmentLength = calculateSegmentLength(start, end);
    
    if (segmentLength == 0) {
        return {0, calculateSegmentLength(point, start)};
    }
    
    // 计算投影点参数t
    float t = QPointF::dotProduct(point - start, segment) / (segmentLength * segmentLength);
    t = qBound(0.0f, t, 1.0f);
    
    // 计算投影点坐标
    QPointF projectionPoint = start + segment * t;
    
    // 计算两个所需距离
    float startDistance = calculateSegmentLength(start, projectionPoint);
    float pointDistance = calculateSegmentLength(point, projectionPoint);
    
    return {startDistance, pointDistance};
}

float Path::calculateSegmentLength(const QPointF& start, const QPointF& end) const {
    QPointF diff = end - start;
    return std::sqrt(QPointF::dotProduct(diff, diff));
}