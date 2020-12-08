//#include "register_window.h"
#include "ui_register_window.h"
#include "login.h" //cabecera login.h

login *lg2; //creamos un puntero a la clase login

Register_window::Register_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Register_window)
{
    ui->setupUi(this);
    /*
Le damos texto a los espacios de para la informacion del usuario con el metodo
setPlaceHolder
*/
    ui->line_name->setPlaceholderText("Name");
    ui->line_last->setPlaceholderText("Last Name");
    ui->line_email->setPlaceholderText("Email");
    ui->line_phone->setPlaceholderText("Phone");
    ui->line_user->setPlaceholderText("Username");
    ui->line_pass->setPlaceholderText("Password");
}

Register_window::~Register_window()
{
    delete ui;

}

void Register_window::on_register_btn_clicked()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("base.db");

    if(!db.open()){
        ui->statusbar->showMessage("Connection Succesful to database", 5000);
    }
    else{
        QString name = ui->line_name->text();
        QString last = ui->line_last->text();
        QString phone = ui->line_phone->text();
        QString email = ui->line_email->text();
        QString user = ui->line_user->text();
        QString pass = ui->line_pass->text();

        QSqlQuery qry;
        //creamos una tabla para los usuarios
        qry.prepare("CREATE TABLE IF NOT EXISTS users(name VARCHAR(20), last VARCHAR(20), phone INT(10), email VARCHAR(30), user VARCHAR(20), pass VARCHAR(20));");

        if(!qry.exec()){
            ui->statusbar->showMessage("Cant create a table");
        }
        else{
            ui->statusbar->showMessage("Table Created", 1000);
        }
        //insertamos la informacion en la tabla
        qry.prepare("INSERT INTO users(name, last,phone,email,user,pass)"
                    "VALUES(:name,:last,:phone,:email,:user,:pass)");
        //validamos que los campos no esten vacios
           if(name.isEmpty() || last.isEmpty() || phone.isEmpty() || email.isEmpty() || email.isEmpty() || user.isEmpty() || pass.isEmpty()){
               QMessageBox::critical(this, "INFO", "All spaces are requerided");
           }
           else{
               //agregamos a inforamcion a la base de datos
           qry.bindValue(":name",name);
           qry.bindValue(":last",last);
           qry.bindValue(":phone",phone);
           qry.bindValue(":email",email);
           qry.bindValue(":user",user);
           qry.bindValue(":pass",pass);
           if(!qry.exec()){
               QMessageBox::critical(this, "Info","Registration failed!");
           }
           else{
               /*SI la insercion fue correcta, cerramos la ventana y volvemos  a la venana de login*/
               QMessageBox::information(this, "Info","Rgistration succesful!");
                hide();
                lg2 = new login(this);
                lg2->show();
           }
           }
    }

}
