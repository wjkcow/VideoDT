#ifndef TRACKER_INFO_H
#define TRACKER_INFO_H

#include <QString>
#include <vector>
#include <QColor>

class TrackingTask;
class Dectector;

class TrackerInfo{
public:
    TrackerInfo(const QString& name_, QColor color_);
    QString name;
    QColor color;
};
#endif // TYPES

