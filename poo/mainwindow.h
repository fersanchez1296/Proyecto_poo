#define MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QTableWidgetItem>
/*
Se añaden las cabeceras necesarias para trabajar con la base de datos ademas de los cuadros de diaologo
y para trabajar el widget TableWidget
*/
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showdatos(); //funcion mostrar datos

private slots:
    void on_actionClose_triggered();

    void on_actionClose_session_triggered();

    void on_add_btn_clicked();

    void on_out_btn_clicked();

    void on_close_btn_clicked();

    void on_save_btn_clicked();

    void on_tableItems_itemClicked(QTableWidgetItem *item);

    void on_delete_btn_clicked();

    void on_actionClear_BD_triggered();

    void on_help_btn_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db; //instancia a la clase QsqlDatabase
    QSqlTableModel *table;//instancia a la clase QsqlTableModel
    int con; //variable de tipo int
};

//#endif // MAINWINDOW_H
