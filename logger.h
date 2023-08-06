#ifndef LOGGER_H
#define LOGGER_H

#include <QWidget>
#include <QtWidgets>

class Logger : public QWidget
{
    Q_OBJECT
    QLineEdit* line;
public:
    explicit Logger(QWidget *parent = nullptr);
    void clear_log();
    void log_sym(QString);

signals:

};

#endif // LOGGER_H
