#ifndef NEWDATATEMPLATEWIDGET_H
#define NEWDATATEMPLATEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QStandardItem>

#include "header/ropageoption/robmanual/common.h"
#include "decode_typestructs.h" // 需要用到结构体decode_type_property


/* **************************************************** */
/* ************ 【新数据声明】/【数据声明】界面 ************ */
/* *************************************************** */
class NewDataTemplateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NewDataTemplateWidget(ProgramData::DataTypes dataType, QString name, QWidget *parent = 0);
    ~NewDataTemplateWidget();

    QWidget *tipsWidget;

    QLabel *dataTypeKeyLabel;
    QLabel *dataTypeValLabel;
    QLabel *currTaskKeyLabel;
    QLabel *currTaskValLabel;

    QWidget *contentWidget;

    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QPushButton *nameBtn;

    QLabel *scopeLabel;
    QComboBox *scopeComboBox;

    QLabel *storageTypeLabel;
    QComboBox *storageTypeComboBox;

    QLabel *taskLabel;
    QComboBox *taskComboBox;

    QLabel *moduleLabel;
    QComboBox *moduleComboBox;

    QLabel *routineLabel;
    QComboBox *routineComboBox;

    QLabel *dimensionLabel;
    QComboBox *dimensionComboBox;
    QLineEdit *dimensionLineEdit;
    QPushButton *dimensionBtn;


    QWidget *buttonWidget;
    QPushButton *initValBtn;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

signals:
    void okBtnClicked();
    void cancelBtnClicked();

public slots:
    void initValBtnClicked();

    void scopeComboBoxResponded(int scopeType);
    void storageTypeComboBoxResponded(int storageType);
    void taskComboBoxResponded(QString curTaskStr);
    void moduleComboBoxResponded(QString curModuleStr);
    void routineComboBoxResponded(QString curRoutineStr);
    void dimensionComboBoxResponded(int dimension);

private:
    decode_type_property newDataProperty;
    //void setDefaultProperty(decode_type_property *property);  // 设置初始属性
    //void initNewDataProperty(decode_type_property *property);

    QStringList scopeTypeStrList;
    QStringList storageTypeStrList;
    QStringList dimensionStrList;
    QStringList taskStrList;
    QStringList moduleStrList;
    QStringList routineStrList;

    QString curTaskNameStr;
    QString curModuleNameStr;
    QString curRoutineNameStr;

};



/* ************************************* */
/* ************ 【编辑】界面 ************ */
/* *********************************** */
class DataEditTemplateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DataEditTemplateWidget(ProgramData::DataTypes dataType, QString name, QWidget *parent = 0);
    ~DataEditTemplateWidget();

    /* 提示栏 */
    QWidget *tipsWidget;
    QLabel *currentKeyLabel;
    QLabel *currentValLabel;
    QLabel *tipsLabel;

    /* 内容栏 */
    QWidget *contentWidget;
    QTableView *contentTabView;
    QStandardItemModel *contentModel;


    /* 按钮操作栏 */
    QWidget *buttonWidget;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QPushButton *undoBtn;
    QPushButton *boolTrueBtn;
    QPushButton *boolFalseBtn;


signals:
    void okBtnClicked();
    void cancelBtnClicked();

public slots:
    //void initValBtnClicked();

};


/* ************************************* */
/* ************ 【定义】界面 ************ */
/* *********************************** */
class DataDefineTemplateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DataDefineTemplateWidget(ProgramData::DataTypes dataType, QString name, QWidget *parent = 0);
    ~DataDefineTemplateWidget();

    /* 提示栏 */
    QWidget *tipsWidget;
    QLabel *titleLabel;
    QLabel *currentKeyLabel;
    QLabel *currentValLabel;
    QLabel *tipsLabel;
    QLabel *methodLabel;
    QComboBox *methodComboBox;
    QLabel *numOfPointLabel;
    QComboBox *numOfPointComboBox;

    /* 内容栏 */
    QWidget *contentWidget;
    QTableView *contentTabView;
    QStandardItemModel *contentModel;


    /* 按钮操作栏 */
    QWidget *buttonWidget;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QPushButton *modPosBtn;
    QPushButton *positonsBtn;

    QMenu *positionsBtnMenu;
    QAction *resetAllAction;
    QAction *loadAction;
    QAction *saveAction;


signals:
    void okBtnClicked();
    void cancelBtnClicked();

public slots:
    //void initValBtnClicked();

};


/* ***************************************** */
/* ************ 【警告对话框】界面 ************ */
/* **************************************** */
class WarningDialogTemplateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WarningDialogTemplateWidget(QString message, QWidget *parent = 0);
    ~WarningDialogTemplateWidget();

    QWidget *mainWidget;
    QLabel *topWarningLabel;

    QLabel *warningIcon;
    QLabel *warningMessage;

    QPushButton *yesBtn;
    QPushButton *noBtn;

signals:
    void yesBtnClicked();
    void noBtnClicked();

protected:
    //void moveEvent(QMoveEvent *);
    //void resizeEvent(QResizeEvent *);

};


#endif // NEWDATATEMPLATEWIDGET_H
