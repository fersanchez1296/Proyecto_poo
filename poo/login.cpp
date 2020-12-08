#include "login.h"
#include "ui_login.h"
#include <QPixmap> //libreriA necesaria para agregar imagenes a nuestro GUI
#include <QMessageBox> //Librerira necesaria para mostrar cuadros de dialogo

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    /*
Con este código agregamos y configuramos el tamaño de nuestro imagen principal
el login.
Se utilizan los metodos setPlaceHolder para mostrar un texto dentro
de las lineEdit de GUI.
    */

    QPixmap pix(":/icons/icons/icon.png");
    ui->icon->setPixmap(pix.scaled(131,111,Qt::KeepAspectRatio));
    ui->line_user->setPlaceholderText("          Username");
    ui->line_pass->setPlaceholderText("          Password");
}

login::~login()
{
    delete ui;
}


void login::on_log_btn_clicked()
{
    /*
    acciones realizadas al presionar el boton log_btn
    */
    db = QSqlDatabase::addDatabase("QSQLITE"); //definción de la base de datos
    db.setDatabaseName("base.db"); //nombre de la base de datos
    QString username = ui->line_user->text(); //variables asignados a los campos de texto de la GUI
    QString password = ui->line_pass->text();

    if(!db.open()){ //comprobamos si se puede abrir la base de datos
        ui->statusbar->showMessage("Conection failed to database", 5000); //si no se puede abrir se muestra un mensaje que dura 5 segundos
    }
    else{ //si la base de datos se abre, se realizan estas acciones
        QSqlQuery qry(QSqlDatabase::database("QSQLITE")); //intanciamos la calse QsqlQuery
        qry.prepare("SELECT * FROM users WHERE user = :user AND pass = :pass"); //realizamos una consulta con el metodo prepare
        qry.bindValue(":user",username); // pasamos el valor a la consulta
        qry.bindValue(":pass",password);// pasamos el valor a la consulta

        if(!qry.exec()){ //comprobamos si se pudo realizar la consulta
            ui->statusbar->showMessage("Credenciales no encontradas");
        }
        else{ // si se pudo realizar la consulta se realizan las siguientes acciones
            while(qry.next()){  //mediante el bucle while buscamos dentro de la base de datos
                QString userDB = qry.value(4).toString(); //se crean dos variables para buscar la informcion dentro
                QString passDB = qry.value(5).toString();

                if(!(userDB == username and passDB == password)){
                        QMessageBox::information(this,"INFO","Wrong data");// mensaje mostrado si no encuentro la información
                }
                else{
                    /*
si la informacion se encuentra, ocultamos la ventana de login y mostramos la ventana de menú
                        */
                    hide();
                    Menu = new menu;
                    Menu->show();
                }
            }
        }
    }
}


void login::on_sign_btn_clicked()
{

    /*
SI el usuario no tiene cuenta puede registrarse al presionar este boton
se oculta laventana de login y se muestra la de registro.
*/
    hide();
    registerwindow = new Register_window;
    registerwindow->show();
}
