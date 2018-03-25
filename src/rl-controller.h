#ifndef RL_CONTROLLER_H
#define RL_CONTROLLER_H

#include <QThread>

class QRlController : public QThread
{
  Q_OBJECT

public:
  QRlController();

protected:
  void run() Q_DECL_OVERRIDE;

signals:
  void command(const QString &cmd);
};

#endif /* RL_CONTROLLER_H */
