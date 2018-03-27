#ifndef CMD_CONTROLLER_H
#define CMD_CONTROLLER_H

#include <QObject>

class QRlController;
class QCmdController : public QObject
{
  Q_OBJECT

public:
  QCmdController(QRlController *rl);
  ~QCmdController() Q_DECL_OVERRIDE;

public slots:
  void onCommand(const QString &cmd);

private:
  QRlController *mRlController;
};

#endif /* CMD_CONTROLLER_H */
