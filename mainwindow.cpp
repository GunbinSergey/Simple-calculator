#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget* c_widget = new QWidget;
    this->setCentralWidget(c_widget);

    //Раставляем зоны для кнопок и экран
    QVBoxLayout *lay_main = new QVBoxLayout(c_widget);
    QGridLayout *lay_buts = new QGridLayout;

    resize(300, 300);

    lcd_label = new QLabel;
    lcd_label->setMaximumSize(800, 200);
    lcd_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lcd_label->setText(label_base + "0");

    his_label = new QLineEdit;
    his_label->setReadOnly(true);

    oper = new QQueue<QString>;
    values = new QQueue<double>;
    que_len = 0;

    lay_main->addWidget(his_label);
    lay_main->addWidget(lcd_label);
    lay_main->addLayout(lay_buts);
    add_buttons(lay_buts);



    //Скелинг зон относительно друг друга
    //lay_main->setStretch(0, 1000);
    //lay_main->setStretch(1, 80);
    //lay_main->setStretch(2, 800);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_buttons(QGridLayout *lay)
{
    QString symbs    = "C  ="
                       "789+"
                       "456-"
                       "123*"
                       " 0./";
    int rows = symbs.length() / 4;
    int cols = symbs.length() / 5;

    for (int r = 0; r < rows; ++r) {
         for (int c = 0; c < cols; ++c)
         {
            QPushButton* but = new QPushButton(QString(symbs[c+r*cols]));
            connect(but, SIGNAL(clicked()), this, SLOT(cal_but_click()));
            lay->addWidget(but, r, c);
         }

    }
}

void MainWindow::add_sym(QString sym)
{
    QString at_is =  lcd_label->text();



    //QString to_be = at_is+ sym;
    QString to_be = Is_number(at_is, sym);
    lcd_label->setText(to_be);
}

void MainWindow::cal_but_click()
{
    //Обработка нажатой клавиши
    QPushButton *sender = static_cast<QPushButton*>(QObject::sender());
    QString sym = sender->text();
    if (sym == "C")
    {
        deep_clear_label();
    }
    else if (sym == "+" || sym == "-" || sym == "*" || sym == "/")
    {
       add_oper(sym);
    }
    else if (sym == "=")
    {
        calculate();
    }
    else
    {
        add_sym(sym);
    }

}


void MainWindow::clear_label()
{
    lcd_label->setText(label_base + "0");

}

void MainWindow::deep_clear_label()
{
    clear_label();
    oper->clear();
    values->clear();
    que_len = 0;
}

void MainWindow::add_oper(QString op)
{
    //Занесение в очередь оператора и первого операнда
    oper->enqueue(op);
    values->enqueue(get_value());
    que_len++;
    clear_label();


}

QString MainWindow::Is_number(QString was, QString sym)
{
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

double MainWindow::get_value()
{
    QString value_str = lcd_label->text();
    value_str = value_str.replace(label_base, "");
    double val = value_str.toDouble();
    return val;
}

void MainWindow::calculate()
{
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
    if (operat == "+")
    {
        result = first + second;
    }
    else if (operat == "-")
    {
        result = first - second;
    }
    else if (operat == "*")
    {
        result = first * second;
    }
    else if (operat == "/")
    {
        result = first / second;
    }


    //values->enqueue(result);
    lcd_label->setText(label_base + QString::number(result));
    //values->enqueue(get_value());
    //que_len++;
    qDebug() << QString::number(que_len);
}

