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

    resize(300, 400);

    lcd_label = new QLCDNumber;
    lcd_label->setMaximumSize(800, 200);
    lcd_label->setDigitCount(20);
    his_label = new QLineEdit;
    his_label->setReadOnly(true);



    lay_main->addWidget(his_label);
    lay_main->addWidget(lcd_label);
    lay_main->addLayout(lay_buts);
    Add_buttons(lay_buts);

    //Скелинг зон относительно друг друга
    lay_main->setStretch(0, 1000);
    lay_main->setStretch(1, 80);
    lay_main->setStretch(2, 800);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Add_buttons(QGridLayout *lay)
{
    QString symbs    = "C  ="
                       "789+"
                       "456-"
                       "123*"
                       " 0,/";
    int rows = symbs.length() / 4;
    int cols = symbs.length() / 5;

    for (int r = 0; r < rows; ++r) {
         for (int c = 0; c < cols; ++c)
         {
            QPushButton* but = new QPushButton(QString(symbs[c+r*cols]));
            connect(but, SIGNAL(clicked()), this, SLOT(add_sym()));
            lay->addWidget(but, r, c);
         }

    }
}

void MainWindow::add_sym()
{
    QPushButton *sender = static_cast<QPushButton*>(QObject::sender());


    QString at_is = QString::number(lcd_label->value());
    if (at_is == "0")
        at_is = "";

    QString to_be = at_is+sender->text();
    lcd_label->display(to_be);

}

