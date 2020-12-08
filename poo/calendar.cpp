#include "calendar.h"
#include "ui_calendar.h"
#include "menu.h"
QString fecha;
menu *m2;
calendar::calendar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::calendar)
{
    ui->setupUi(this);
    mostrarDatos(fecha);
}

calendar::~calendar()
{
    delete ui;
}

void calendar::mostrarDatos(QString fecha)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("registro.db");
    if(!database.open()){
        qDebug() << "conexion fallida 1";
    }
    else{
        qDebug() << "conexion exitosa";
        QSqlQuery qry;
        qry.prepare("SELECT * FROM event WHERE fechas = ?");
        qry.addBindValue(fecha);
        if(qry.exec()){
        int fila=0;
        ui->tableCalendar->setRowCount(0);
        while(qry.next()){

            ui->tableCalendar->insertRow(fila);
            ui->tableCalendar->setItem(fila,0, new QTableWidgetItem(qry.value(1).toByteArray().constData()));
            ui->tableCalendar->setItem(fila,1, new QTableWidgetItem(qry.value(2).toByteArray().constData()));
            fila++;
        }
        }
        else{
            qDebug() << "conexion fallida";
        }
    }
}


void calendar::on_agregar_btn_clicked()
{
    QString hora = ui->line_hora->text();
    QString evento = ui->line_evento->text();
    QString fechas = ui->line_fecha->text();

   QSqlQuery qry;

   qry.prepare("CREATE TABLE IF NOT EXISTS event (fechas TIMESTAMP, hora VARCHAR(30), evento VARCHAR(30));" );
   if( !qry.exec() ){
       qDebug() << qry.lastError();
   }
     else{
       qDebug()  << "created table";
   }

   qry.prepare("INSERT INTO event (fechas, hora, evento)"
               "VALUES(:fechas,:hora,:evento)");
       //if(id.isEmpty()){
         //  qDebug() << "no se puede agregar";
       //}
       //else{
       qry.bindValue(":fechas",fechas);
       qry.bindValue(":hora",hora);
       qry.bindValue(":evento",evento);


       if(qry.exec()){
           qDebug()  << "Registration succesfull";
           mostrarDatos(fecha);
       }
       else{
           qDebug()  << "Registration failed";
           qDebug() << qry.lastError();
       }
       //}
}

void calendar::on_calendar_2_activated(const QDate &date)
{
    //ui->line_fecha->clear();
    QString dia = date.toString("d");
    QString mes = date.toString("MM");
    QString anio = date.toString("yyyy");

    fecha = anio+"-"+mes+"-"+dia;
    ui->line_fecha->setText(fecha);
    mostrarDatos(fecha);
}



void calendar::on_pushButton_clicked()
{
    m2 = new menu;
    m2->show();
}
