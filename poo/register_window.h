#define REGISTER_WINDOW_H
#define REGISTER_WINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

/*
Librerias necesarias para los comando sqlite
*/

namespace Ui {
class Register_window;
}

class Register_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Register_window(QWidget *parent = nullptr);
    ~Register_window();

private slots:
    void on_register_btn_clicked();

private:
    Ui::Register_window *ui;
    QSqlDatabase db; //instancia de la clase QsqlDatabase
};

//#endif // REGISTER_WINDOW_H
