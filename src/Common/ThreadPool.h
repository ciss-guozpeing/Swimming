#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <QObject>
#include <QThreadPool>
#include <QRunnable>

class ThreadPool: public QObject
{
public:
    static ThreadPool* getInstance();
    ThreadPool();
    void submitTask(QRunnable* task, bool autoDelete=true);

};

#endif // THREADPOOL_H
