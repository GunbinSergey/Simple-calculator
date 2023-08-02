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

    //Метод отвечающий за обработку и вывод операндов
    scr = new Screen;

    lay_main->addWidget(scr);;
    lay_main->addLayout(lay_buts);
    add_buttons(lay_buts);

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


void MainWindow::cal_but_click()
{
    //Обработка нажатой клавиши
    QPushButton *sender = static_cast<QPushButton*>(QObject::sender());
    QString sym = sender->text();
    if (sym == "C")
    {
        scr->deep_clear_label();
    }
    else if (sym == "+" || sym == "-" || sym == "*" || sym == "/")
    {
       scr->add_oper(sym);
    }
    else if (sym == "=")
    {
        scr->calculate();
    }
    else
    {
        scr->add_sym(sym);
    }

}





