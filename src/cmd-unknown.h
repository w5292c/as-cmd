#ifndef CMD_UNKNOWN_H
#define CMD_UNKNOWN_H

#include <cmd-base.h>

class QCmdUnknown : public QCmdBase
{
  Q_OBJECT

public:
  QCmdUnknown();
  ~QCmdUnknown() Q_DECL_OVERRIDE;

protected:
  void process() Q_DECL_OVERRIDE;

};

#endif /* CMD_UNKNOWN_H */
