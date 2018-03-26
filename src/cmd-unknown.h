#ifndef CMD_UNKNOWN_H
#define CMD_UNKNOWN_H

#include <cmd-base.h>

class QCmdUnknown : public QCmdBase
{
  Q_OBJECT

public:
  QCmdUnknown();

protected:
  void run() Q_DECL_OVERRIDE;

};

#endif /* CMD_UNKNOWN_H */
