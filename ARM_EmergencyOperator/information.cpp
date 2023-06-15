#include "information.h"
#include "ui_information.h"

InformWindow::InformWindow(QWidget *p) :
    QMainWindow(p)
    , ui(new Ui::InformWindow)
{
    ui->setupUi(this);

    model = new QStringListModel(this);

    QStringList stringList;

    QFile textFile("history.txt");
    if(!textFile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0,"Error",textFile.errorString());
    }

    QTextStream textStream(&textFile);
    while (true)
    {
        QString line = textStream.readLine();
        if (line.isNull())
            break;
        else
            stringList.append(line); // populate the stringlist
    }

    model->setStringList(stringList);

    // Glue model and view together
    ui->listView->setModel(model);

    // if you want to add additional feature to listview.
    ui->listView->
            setEditTriggers(QAbstractItemView::AnyKeyPressed |
                            QAbstractItemView::DoubleClicked);
}

InformWindow::~InformWindow()
{
    delete ui;
}

void InformWindow::on_clear_history_clicked()
{
    model->setStringList( QStringList{} );
    model->removeRows( 0, model->rowCount() );
    QFile f("history.txt");
    if(f.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString s;
        QTextStream t(&f);
        while(f.atEnd())
        {
            QString line = t.readLine();
            if(!line.contains("DELETE"))
                s.append(line + "\n");
        }
        f.resize(0);
        t << s;
        f.close();
    }
    else
    {
        qDebug("no open");
    }
}

