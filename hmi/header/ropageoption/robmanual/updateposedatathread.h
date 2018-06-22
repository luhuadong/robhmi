#ifndef UPDATEPOSEDATATHREAD_H
#define UPDATEPOSEDATATHREAD_H

#include <QThread>

class UpdatePoseDataThread : public QThread
{
    Q_OBJECT
public:
    explicit UpdatePoseDataThread(QObject *parent = 0);
    ~UpdatePoseDataThread();

signals:
    //void poseDataUpdated(QStringList poseDataStrList);
    //void poseDataUpdated(QString poseData[]);
    void poseDataUpdated(QString *poseData);

public slots:

protected:
    void run();
};

#endif // UPDATEPOSEDATATHREAD_H
