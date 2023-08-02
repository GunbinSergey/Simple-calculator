#include "screen.h"

Screen::Screen()
{
    QVBoxLayout *layV = new QVBoxLayout(this);

    lcd_label = new QLabel();

    lcd_label->setMaximumSize(800, 200);
    lcd_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lcd_label->setText(label_base + "0");

    his_label = new QLineEdit;
    his_label->setReadOnly(true);

    oper = new QQueue<QString>;
    values = new QQueue<double>;
    que_len = 0;

    layV->addWidget(his_label);
    layV->addWidget(lcd_label);
}

void Screen::add_sym(QString sym)
{
    //Метод изменения записи н экране
    QString at_is =  lcd_label->text();
    QString to_be = Is_number(at_is, sym);
    lcd_label->setText(to_be);
}

void Screen::clear_label()
{
    //Очистка экрана
    lcd_label->setText(label_base + "0");
}

void Screen::deep_clear_label()
{
    //Очистка экрана с очисткой очередей операндов и операторов
    clear_label();
    oper->clear();
    values->clear();
    que_len = 0;
}

void Screen::add_oper(QString op)
{
    //Занесение в очередь оператора и первого операнда
    oper->enqueue(op);
    values->enqueue(get_value());
    que_len++;
    clear_label();


}

QString Screen::Is_number(QString was, QString sym)
{
    //Проверка корректности введённого числа
    QString s_val = was.replace(label_base, "");

    if (s_val == "0" && sym != ".")
    {
        s_val = "";
    }

    QString ns_val = s_val + sym;
    bool be_new;
    double val = ns_val.toDouble(&be_new);
    if (be_new)
    {
        return label_base + ns_val;
    }
    else
        return was;

}

double Screen::get_value()
{
    //Метод выстаскивания числа с экрана калькулятора
    QString value_str = lcd_label->text();
    value_str = value_str.replace(label_base, "");
    double val = value_str.toDouble();
    return val;
}

double Screen::val_calc(double fir, double second, QString op)
{
    double result = 0;
    if (op == "+")
    {
        result = fir + second;
    }
    else if (op == "-")
    {
        result = fir - second;
    }
    else if (op == "*")
    {
        result = fir * second;
    }
    else if (op == "/")
    {
        result = fir / second;
    }
    return result;
}

void Screen::calculate()
{
    //Метод подготовки рассчёта полученого значения
    values->enqueue(get_value());
    que_len++;

    qDebug() << QString::number(que_len);

    double result = 0;

    if (que_len < 2)
    {
        deep_clear_label();
        return;
    }

    double first = values->dequeue();
    que_len--;
    double second = values->dequeue();
    que_len--;
    QString operat = oper->dequeue();

    result = val_calc(first, second, operat);

    lcd_label->setText(label_base + QString::number(result));
    qDebug() << QString::number(que_len);
}
