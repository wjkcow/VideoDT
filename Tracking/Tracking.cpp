#include "Tracking/Tracking.h"
#include "Dectector/TrackingTask.h"
#include <QFuture>
#include <QHash>
#include <QRect>
#include <QFutureWatcher>

class TrackingWorker : QObject{
    Q_OBJECT
public:
    TrackingWorker(TrackingTask task) : m_task(task){}
    ~TrackingWorker(){delete m_future;
                      delete m_future_watcher;}
    void run(){


    }
public slots:
    void my_work_done();
private:
    void parallel_task_run(const QString& path){

    }
    TrackingTask m_task;
    QHash<int, QRect> results;
    QFuture<void>* m_future;
    QFutureWatcher<void>* m_future_watcher;
};
