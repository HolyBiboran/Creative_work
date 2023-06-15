#include "arm_emergency_operator.h"
#include "ui_arm_emergency_operator.h"
#include <fstream>
using namespace std;

ARM_emergency_operator::ARM_emergency_operator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ARM_emergency_operator)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./testDB.db");

    if(db.open())
    {
        qDebug("open");
    }
    else
    {
        qDebug("no open");
    }


    query = new QSqlQuery(db);
    query->exec("CREATE TABLE ListOfCalls(ФИО TEXT, Номер_телефона TEXT, Причина_звонка TEXT, Срочность TEXT, Район TEXT, Улица TEXT, Выполнен BOOL);");

    model = new QSqlTableModel(this, db);
    model->setTable("ListOfCalls");
    model->select();

    ui->tableView->setModel(model);

    dbOp = QSqlDatabase::addDatabase("QSQLITE");
    dbOp.setDatabaseName("./testDB.db");

    if(dbOp.open())
    {
        qDebug("open");
    }
    else
    {
        qDebug("no open");
    }


    queryOp = new QSqlQuery(dbOp);
    queryOp->exec("CREATE TABLE ListOfOperators(Индекс_жетона INT, Номер_пейджера TEXT, Номер_машины TEXT, Район_патрулирования TEXT, Занятость BOOL);");
    modelOp = new QSqlTableModel(this, dbOp);
    modelOp->setTable("ListOfOperators");
    modelOp->select();


    ui->tableView_2->setModel(modelOp);



    dbCont = QSqlDatabase::addDatabase("QSQLITE");
    dbCont.setDatabaseName("./testDB.db");

    if(dbCont.open())
    {
        qDebug("open");
    }
    else
    {
        qDebug("no open");
    }


    queryCont = new QSqlQuery(dbCont);
    queryCont->exec("CREATE TABLE ListOfContacts(Тип_службы TEXT, Контактный_номер_диспетчера TEXT, Район TEXT);");

    modelCont = new QSqlTableModel(this, dbCont);
    modelCont->setTable("ListOfContacts");
    modelCont->select();


    ui->tableView_3->setModel(modelCont);

    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_3->horizontalHeader()->setStretchLastSection(true);

    info = new InformWindow;
    connect(info, &InformWindow::firstWindow, this, &ARM_emergency_operator::show);

    QFile history("/history.txt");
    fstream history1;
    history1.open("./history.txt"); // append instead of overwrite
}

ARM_emergency_operator::~ARM_emergency_operator()
{
    delete ui;
}



void ARM_emergency_operator::on_tableView_clicked(const QModelIndex &index)
{
    row=index.row();
}



void ARM_emergency_operator::on_pushButton_clicked()
{
    model->insertRow(model->rowCount());
}


void ARM_emergency_operator::on_pushButton_2_clicked()
{
    model->removeRow(row);
}


void ARM_emergency_operator::on_tableView_2_clicked(const QModelIndex &index)
{
    rowOp=index.row();
}


void ARM_emergency_operator::on_pushButton_3_clicked()
{
    modelOp->insertRow(modelOp->rowCount());
}


void ARM_emergency_operator::on_pushButton_4_clicked()
{
    modelOp->removeRow(rowOp);
}


void ARM_emergency_operator::on_tableView_3_clicked(const QModelIndex &index)
{
    rowCont=index.row();
}


void ARM_emergency_operator::on_pushButton_5_clicked()
{
    modelCont->insertRow(modelCont->rowCount());
}


void ARM_emergency_operator::on_pushButton_6_clicked()
{
    modelCont->removeRow(rowCont);
}


void ARM_emergency_operator::on_information_clicked()
{
    info->show();
}


void ARM_emergency_operator::on_identifyIndex_editingFinished()
{
    if(ui->identifyIndex->text().trimmed().isEmpty())
    {
            QMessageBox::warning(this,"Осторожно","Индентификатор введён некорректно\nПодсчёт произведённых звонков производиться не будет");
    }
    else
    {
        Operator_index = ui->identifyIndex->text();
    }
}



void ARM_emergency_operator::on_tableView_pressed(const QModelIndex &index)
{
    QFile fh("history.txt");
    QTextStream t(&fh);
    if(fh.open(QIODevice::ReadWrite | QIODevice::Text)&& (Operator_index!=""))
    {

        for(int i=0; i<=model->rowCount()-1;i++)
            {
                rowComplete=i;
                a=ui->tableView->model()->data(ui->tableView->model()->index(rowComplete,6)).toBool();
                if (a==true)
                {
                    t.readLine();
                    t.readLine();
                    QString stringofINFO;
                    stringofINFO.append(Operator_index);
                    stringofINFO.append(" ");
                    stringofINFO.append(ui->tableView->model()->data(ui->tableView->model()->index(rowComplete,0)).toString());
                    stringofINFO.append(" ");
                    stringofINFO.append(ui->tableView->model()->data(ui->tableView->model()->index(rowComplete,1)).toString());
                    stringofINFO.append(" ");
                    stringofINFO.append(ui->tableView->model()->data(ui->tableView->model()->index(rowComplete,2)).toString());
                    stringofINFO.append(" ");
                    stringofINFO.append(ui->tableView->model()->data(ui->tableView->model()->index(rowComplete,3)).toString());
                    stringofINFO.append(" ");
                    stringofINFO.append(ui->tableView->model()->data(ui->tableView->model()->index(rowComplete,4)).toString());
                    stringofINFO.append(" ");
                    stringofINFO.append(ui->tableView->model()->data(ui->tableView->model()->index(rowComplete,5)).toString());
                    t<<stringofINFO<<endl;
                    model->removeRow(rowComplete);
                }
            }
    }
    fh.close();
}



void ARM_emergency_operator::on_tableView_2_doubleClicked(const QModelIndex &index)
{
    busy=0;
    int g=modelOp->rowCount();
    for (int it=0; it<g;it++)
    {
        a1=ui->tableView_2->model()->data(ui->tableView_2->model()->index(it,4)).toBool();
        if (a1==true)
        {
            busy++;
        };
    };
    if (g==busy)
    {
        QMessageBox::warning(this,"Внимание","Сообщите руководству о необходимости подкреплений");
    };
}



