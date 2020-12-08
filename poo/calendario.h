#define CALENDARIO_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidgetItem>
/*
librerias necesarios para trabajar con la base de datos y mostrar ventas de dialogo
ademas para poder trabajar con el el widget tablewidget
*/
namespace Ui {
class calendario;
}

class calendario : public QWidget
{
    Q_OBJECT

public:
    explicit calendario(QWidget *parent = nullptr);
    ~calendario();
    void mostrarDatos(QString fecha);

private slots:
    void on_calendar_2_activated(const QDate &date);

    void on_agregar_btn_clicked();

    void on_salir_btn_clicked();

private:
    Ui::calendario *ui;
    QSqlDatabase database; //se instancia la clase QsqlDatabase
};

//#endif // CALENDARIO_H
