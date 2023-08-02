#ifndef SCREEN_H
#define SCREEN_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>

class Screen: public QWidget
{
    //Q_OBJECT
    QString Is_number(QString was, QString sym);

public:
    Screen();


    void add_sym(QString);
    void clear_label();
    void deep_clear_label();
    void add_oper(QString);

    double get_value();
    double val_calc(double fir,double second, QString op);
    void calculate();


    QLabel* lcd_label;
    QLineEdit* his_label;

    QQueue<QString>* oper;
    QQueue<double>* values;
    int que_len;
    const QString label_base = "<font size = 12>";
};

#endif // SCREEN_H
