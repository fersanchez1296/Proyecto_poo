//#include "calendario.h"
#include "ui_calendario.h"
#include "menu.h"
QString fecha; //variable que se le pasa a la funcion mostrar datos
menu *m2; //puntero a la clase menu
calendario::calendario(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::calendario)
{
    ui->setupUi(this);
    ui->line_evento->setPlaceholderText("Evento");
    ui->line_hora->setPlaceholderText("Hora");
     mostrarDatos(fecha);
}

calendario::~calendario()
{
    delete ui;
}

void calendario::mostrarDatos(QString fecha)
{
    /*
Se muestran unicamente los datos almacenados en la base de datos
que corresponan con el valor almacenado en la variable fecha
*/
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("base.db");
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

void calendario::on_calendar_2_activated(const QDate &date)
{
    //Se extrae la fecha clickeada por el usuario y se almacena en la variable fecha
    QString dia = date.toString("d");
    QString mes = date.toString("MM");
    QString anio = date.toString("yyyy");

    fecha = anio+"-"+mes+"-"+dia;
    ui->line_fecha->setText(fecha);
    mostrarDatos(fecha); //mostramos en el widget la informacion que corresponda con la fecha almacenada en fecha
}

void calendario::on_agregar_btn_clicked()
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
       if(hora.isEmpty() || evento.isEmpty() || fechas.isEmpty()){
         QMessageBox::critical(this, "INFO", "NO se pueden dejar campos vacios");
       }
       else{
       qry.bindValue(":fechas",fechas);
       qry.bindValue(":hora",hora);
       qry.bindValue(":evento",evento);


       if(qry.exec()){
           QMessageBox::information(this, "INFO", "Informacion agregada con exito");
           mostrarDatos(fecha);
       }
       else{
           QMessageBox::critical(this, "INFO", "No se puede agregar la informacion");
       }
       }
}

void calendario::on_salir_btn_clicked()
{
    m2 = new menu;
    m2->show();
    hide();
}
