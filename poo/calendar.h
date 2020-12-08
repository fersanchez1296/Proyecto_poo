#ifndef CALENDAR_H
#define CALENDAR_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidgetItem>

namespace Ui {
class calendar;
}

class calendar : public QWidget
{
    Q_OBJECT

public:
    explicit calendar(QWidget *parent = nullptr);
    ~calendar();
    void mostrarDatos(QString fecha);

private slots:

    void on_agregar_btn_clicked();

    void on_calendar_2_activated(const QDate &date);

    void on_salir_btn_clicked();

    void on_pushButton_clicked();

private:
    Ui::calendar *ui;
    QSqlDatabase database;

};

#endif // CALENDAR_H
