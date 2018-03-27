#ifndef CMD_HELP_H
#define CMD_HELP_H

#include <cmd-base.h>

class QCmdHelp : public QCmdBase
{
  Q_OBJECT

public:
  QCmdHelp();
  ~QCmdHelp() Q_DECL_OVERRIDE;

protected:
  void process() Q_DECL_OVERRIDE;

};

#endif /* CMD_HELP_H */
