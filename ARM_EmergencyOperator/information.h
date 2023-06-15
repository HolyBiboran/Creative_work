#ifndef INFORMATION_H
#define INFORMATION_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDebug>
#include <QFile>
#include <QDate>
#include <QLineEdit>
#include <QTextStream>
#include <QMessageBox>
#include <QTextCodec>
#include <QStringListModel>

namespace Ui {
class InformWindow;
}

class InformWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InformWindow(QWidget *parent = nullptr);
    ~InformWindow();

signals:
    void firstWindow();

private slots:


    void on_clear_history_clicked();

private:
    Ui::InformWindow *ui;
    QSqlDatabase dbHistory;
    QSqlQuery *queryHistory;
    QSqlTableModel *modelHistory;
    InformWindow *info;
    QStringListModel *model;
    FILE *fp;
    int indI;
};


#endif // INFORMATION_H
