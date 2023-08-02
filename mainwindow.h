#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QQueue>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void add_buttons(QGridLayout*);
    void add_sym(QString);
    void clear_label();
    void deep_clear_label();
    void add_oper(QString);
    QString Is_number(QString was, QString sym);
    double get_value();
    void calculate();


    QLabel* lcd_label;
    QLineEdit* his_label;

    QQueue<QString>* oper;
    QQueue<double>* values;
    int que_len;
    const QString label_base = "<font size = 12>";

private slots:
    void cal_but_click();
};
#endif // MAINWINDOW_H
