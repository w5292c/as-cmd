#ifndef CMD_OPTIONS_H
#define CMD_OPTIONS_H

#include <cmd-base.h>

class QCmdOptions : public QCmdBase
{
  Q_OBJECT

public:
  QCmdOptions();

protected:
  void execute() Q_DECL_OVERRIDE;

};

#endif /* CMD_OPTIONS_H */
