#ifndef CMD_BASE_H
#define CMD_BASE_H

#include <QThread>

class QCmdBase : public QThread
{
  Q_OBJECT

public:
  QCmdBase();
  ~QCmdBase();

signals:
  void started();
  void finished();
};

#endif /* CMD_BASE_H */
