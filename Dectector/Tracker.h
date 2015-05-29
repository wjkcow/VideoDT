#ifndef TRACKER_H
#define TRACKER_H

#include <QString>
#include <vector>
#include <QColor>

class TrackingTask;
class Dectector;

class Tracker{  
public:
    Tracker(const QString& name_, QColor color_);
    QString name;
    QColor color;
};
#endif // TYPES

