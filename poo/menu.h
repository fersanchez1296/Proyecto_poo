#define MENU_H
#define MENU_H

#include <QWidget>
#include "mainwindow.h"
#include "calendario.h"

/*
Se incluyen las cabeceras de los archivos mainwindow y calendario
*/
namespace Ui {
class menu;
}

class menu : public QWidget
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

private slots:
    void on_agenda_clicked();

    void on_calendario_clicked();

private:
    Ui::menu *ui;
    MainWindow *mainwindow; //se crea un puntero a la clase MainWindow
    calendario *cal; //se crea un puntero a la clase calendario
};

//#endif // MENU_H
