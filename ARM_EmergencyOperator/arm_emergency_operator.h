#ifndef ARM_EMERGENCY_OPERATOR_H
#define ARM_EMERGENCY_OPERATOR_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QFile>
#include <QDate>
#include <QLineEdit>
#include <QTextStream>
#include <information.h>
#include <QMessageBox>
#include <QTextCodec>


QT_BEGIN_NAMESPACE
namespace Ui { class ARM_emergency_operator; }
QT_END_NAMESPACE

class ARM_emergency_operator : public QMainWindow
{
    Q_OBJECT

public:
    ARM_emergency_operator(QWidget *parent = nullptr);
    ~ARM_emergency_operator();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_tableView_3_clicked(const QModelIndex &index);

    void on_information_clicked();

    void on_identifyIndex_editingFinished();

    void on_tableView_pressed(const QModelIndex &index);

    void on_tableView_2_doubleClicked(const QModelIndex &index);

private:
    Ui::ARM_emergency_operator *ui;
    QSqlDatabase db, dbOp, dbCont;
    QSqlQuery *query, *queryOp, *queryCont;
    QSqlTableModel *model, *modelOp, *modelCont;
    InformWindow *info;
    FILE *fp;


    int row, rowOp, rowCont, rowComplete, row1,column1, busy, g;
    bool role, a, a1;
    QString Operator_index;
};
#endif // ARM_EMERGENCY_OPERATOR_H
