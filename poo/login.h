#define LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "register_window.h"
#include "menu.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
/*
se añade la cabecera del archivo register_window.h que es la que nos
permite abrir la ventana de registro

se añade la cabecera del archivo menu.h que es la que nos
permite abrir la ventana de menu

se añaden las librerias necesarias para la conexióna la base de datos,
para realizar consultas y mostrar errores posibles que ocurran.
*/
QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_log_btn_clicked();

    void on_sign_btn_clicked();

private:
    Ui::login *ui;
    Register_window *registerwindow; //Se crea un punturo a la clase Register_window
    menu *Menu; // se crea un puntero a la clase menu
    QSqlDatabase db; // se crea una instancia a la clase QsqlDatabase
};
//#endif // LOGIN_H
