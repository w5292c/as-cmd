#ifndef CMD_VERBOSE_H
#define CMD_VERBOSE_H

#include <cmd-base.h>

class QCmdVerbose : public QCmdBase
{
  Q_OBJECT

public:
  QCmdVerbose(bool show, bool on = false);
  ~QCmdVerbose() Q_DECL_OVERRIDE;

protected:
  void process() Q_DECL_OVERRIDE;

private:
  bool mOn;
  bool mShow;
};

#endif /* CMD_VERBOSE_H */
