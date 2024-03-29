﻿#include "ThreadPool.h"
static ThreadPool* INSTANCE =nullptr;
ThreadPool::ThreadPool():QObject()
{
    QThreadPool::globalInstance()->setMaxThreadCount(15);
}

ThreadPool* ThreadPool::getInstance()
{
    if(!INSTANCE){
        INSTANCE = new ThreadPool;
    }
    return INSTANCE;
}

void ThreadPool::submitTask(QRunnable* task, bool autoDelete)
{
    task->setAutoDelete(autoDelete);
    QThreadPool::globalInstance()->start(task);
}

