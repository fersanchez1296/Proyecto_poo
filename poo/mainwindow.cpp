//#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"
#include <QMessageBox>
#include <QTableWidgetItem>
/*
Se incluye la cabecera menu.h y la biblioteca QTableWidgetItem
*/
menu *Menu; //Se crea un puntero a la clase menu
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    con = -1;  //se inicializa una variable en el constructor
    showdatos(); //se incializa la funcion showdatos()
}

MainWindow::~MainWindow()
{
    db.close(); //se cierra la base datos
    delete ui;
}

void MainWindow::showdatos()
{
    db= QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("base.db");
    if(db.open()){
        QSqlQuery qry;
        qry.prepare("SELECT * FROM schedule"); // hacemos una consulta a la base de datos
        if(!qry.exec()){
            QMessageBox::critical(this, "ERROR", "Cant open database");
        }
        else{
            /*
Añadimos los datos de nuestra base de datos a nuestro tablewidget
            */
            int cols=0;
            ui->tableItems->setRowCount(0);
            while(qry.next()){
                ui->tableItems->insertRow(cols);
                ui->tableItems->setItem(cols,0, new QTableWidgetItem(qry.value(1).toByteArray().constData()));
                ui->tableItems->setItem(cols,1, new QTableWidgetItem(qry.value(2).toByteArray().constData()));
                ui->tableItems->setItem(cols,2, new QTableWidgetItem(qry.value(3).toByteArray().constData()));
                ui->tableItems->setItem(cols,3, new QTableWidgetItem(qry.value(4).toByteArray().constData()));
                cols++;
            }
        }
    }
    else{
        QMessageBox::critical(this, "ERROR", "Cant open database");
    }
}

void MainWindow::on_actionClose_triggered()
{
    QApplication::quit();
    //cerramos la aplicacion con el boton cerrar en el menu superior
}

void MainWindow::on_actionClose_session_triggered()
{
// llamamos a la ventana menu y cerramos la actual
    Menu = new menu;
    Menu->show();
    hide();
}

void MainWindow::on_add_btn_clicked()
{
    /*
Añadimos informacion a nuestra base de datos.
*/
        QString name = ui->line_name->text();
        QString last = ui->line_last->text();
        QString phone = ui->line_phone->text();
        QString date = ui->line_date->text();

        QSqlQuery qry;
        qry.prepare("CREATE TABLE IF NOT EXISTS schedule(id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR(20), last VARCHAR(20), phone INT(10), date VARCHAR(20));");
        if(!qry.exec()){
            QMessageBox::critical(this, "ERROR", "Cant create table");
        }
        else{

        }
        qry.prepare("INSERT INTO schedule(id,name, last, phone, date)"
                    "VALUES(:id,:name,:last,:phone,:date)");
            if(name.isEmpty() || last.isEmpty() || phone.isEmpty() || date.isEmpty()){
                QMessageBox::critical(this, "Info", "All spaces are required");
            }
            else{
            qry.bindValue(":name",name);
            qry.bindValue(":last",last);
            qry.bindValue(":phone",phone);
            qry.bindValue(":date",date);

            if(qry.exec()){
                QMessageBox::information(this, "ADD VALUES", "Values added succesfuly");
                showdatos();
            }
            else{
                QMessageBox::critical(this, "ERROR","Cant add values");
            }
            }
}

void MainWindow::on_out_btn_clicked()
{
    // llamamos a la ventana menu y cerramos la actual
    Menu = new menu;
    Menu->show();
    hide();
}

void MainWindow::on_close_btn_clicked()
{
//cerramos completamente la aplicacion
    db.close();
    QApplication::quit();
}

void MainWindow::on_save_btn_clicked()
{
    //guardamos las modificaciones hechas en nuestra base de datos
    if(db.database().transaction()){
        db.database().commit();
        ui->statusbar->showMessage("Changes saved");
    }
    else{
        ui->statusbar->showMessage("Changes dont saved");
    }
}

void MainWindow::on_tableItems_itemClicked(QTableWidgetItem *item)
{
    //ponemos la informacion seleccionada en un lineEdit
    con = item->row();
    QTableWidgetItem *nombre = ui->tableItems->item(con,0);
    ui->line_status->setText(nombre->text());
}

void MainWindow::on_delete_btn_clicked()
{
//la informacion añadida al lineEdit en el metodo on_tableItems_itemClicked es borrarodo al precionar el boton
    QSqlQuery qry;
    QString numero = ui->line_status->text();
    qry.prepare("DELETE FROM schedule WHERE name= ?");
    qry.addBindValue(numero);
    if(qry.exec()){
    int fila=0;
    ui->tableItems->setRowCount(0);
    while(qry.next()){

        ui->tableItems->insertRow(fila);
        ui->tableItems->setItem(fila,0, new QTableWidgetItem(qry.value(1).toByteArray().constData()));
        ui->tableItems->setItem(fila,1, new QTableWidgetItem(qry.value(2).toByteArray().constData()));
        ui->tableItems->setItem(fila,2, new QTableWidgetItem(qry.value(3).toByteArray().constData()));
        ui->tableItems->setItem(fila,3, new QTableWidgetItem(qry.value(4).toByteArray().constData()));
        fila++;
    }
    showdatos(); //Actualizamos la informacion
    }
}

void MainWindow::on_actionClear_BD_triggered()
{
    /*
borramos toda la informacion de la base de datos
*/
    QSqlQuery qry;
    qry.prepare("DELETE FROM schedule");
    if(qry.exec()){
        QMessageBox::information(this, "INFO", "Se limpiarón todos los registros");
        showdatos();
    }
    else{
        QMessageBox::critical(this, "INFO", "NO se pudo borrar");
    }
}

void MainWindow::on_help_btn_clicked()
{
    QMessageBox::information(this,"Help", "*Debe llenar todos los datos para poder añadir un registro <br>"
                                          "*Presione el icono de candado para regresar al menu        <br"
                                          "*Presione el icono de cerrar carpeta para salir del programa<br>"
                                          "*Seleccione un registro y presione el icono de borrar para eliminar el registro<br>"
                                          "*Presione el icono de guardar para salvar los cambios");
}
