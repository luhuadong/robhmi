#include "header/mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QCoreApplication>

#include "header/DataManage/DataManage.h"

int main(int argc, char *argv[])
{
    int currentExitCode = -1;
    QApplication a(argc, argv);
    //指定显示字体
//    QFont font("helianthus_lu", 12);
//    a.setFont(font);

    QString language[] = {
        "./resource/language/ZH_CN.qm",
        "./resource/language/EN.qm",
    };

    QTranslator qtTranslator;

    do{
        if(currentExitCode > 0){
            qtTranslator.load(language[currentExitCode-1]);
            QCoreApplication::installTranslator(&qtTranslator);
        }

        //数据掉电保存及加载数据
//        DataManage_Init(&quickToData,&robDataBuffer);
        DataManage_Init(&quickToData,&robDataBuffer,&quickToName,&robDataName);

        int fd = -1;

        fd = open(DataManage_FileName,O_CREAT|O_RDWR,0644);
        if(fd == -1){
            perror("open fail:");
            exit(1) ;
        }

        DataManageFile *pFile = &fd;

        DataManage_ReadFile(pFile);//读文件

        close(fd);

        //数据掉电保存及加载数据结束
        MainWindow w;
        w.show();
        //样式
//        QFile styleFile("./resource/qss/qt.qss");
//        styleFile.open(QIODevice::ReadOnly);
//        QString setStyleSheet(styleFile.readAll());
//        a.setStyleSheet(setStyleSheet);

        currentExitCode = a.exec();

    }while(currentExitCode == 1||currentExitCode == 2);

    return 0;
}
