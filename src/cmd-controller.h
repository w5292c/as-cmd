#ifndef CMD_CONTROLLER_H
#define CMD_CONTROLLER_H

#include <QObject>

class QCmdController : public QObject
{
  Q_OBJECT

public:
  QCmdController();

public slots:
  void onCommand(const QString &cmd);

};

#endif /* CMD_CONTROLLER_H */
