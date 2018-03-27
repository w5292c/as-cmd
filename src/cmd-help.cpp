#include "cmd-help.h"

#include <QDebug>

QCmdHelp::QCmdHelp()
{
}

void QCmdHelp::process()
{
  qDebug() << ">>> help - Show help";
  qDebug() << ">>> exit - Exit the application";
  qDebug() << ">>> options - Send 'OPTIONS' request";

  emit done();
}
