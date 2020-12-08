#include "menu.h"
#include "ui_menu.h"

menu::menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}



void menu::on_agenda_clicked()
{
    /*
se llama al puntero mainwindow y se crea una nueva instancia a la clase MainWindow con el puntero this
si se preciona el boton agenda, se abre la ventana para la agenda llamada MainWindow y
se oculta la ventana de menu
*/
    mainwindow = new MainWindow;
    mainwindow->show();
    hide();
}

void menu::on_calendario_clicked()
{
    /*
se llama al puntero cal y se crea una nueva instancia a la clase calendario con el puntero this
si se preciona el boton calendario, se abre la ventana para el calendario llamada calendario y
se oculta la ventana de menu
*/
    cal = new calendario();
    cal->show();
    hide();
}
