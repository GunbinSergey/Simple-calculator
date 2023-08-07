#include "logger.h"

void Logger::clear_log()
{
    line->setText("");
}

void Logger::log_sym(QString add)
{
    QString was = line->text();
    qDebug() << was.compare("=");
    if (was.contains("="))
    {
        was = "";
    }
    QString to_be = was + add;
    line->setText(to_be);
}

Logger::Logger(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* lay = new QVBoxLayout(this);
    line = new QLineEdit();
    lay->addWidget(line);
    line->setReadOnly(true);
}
