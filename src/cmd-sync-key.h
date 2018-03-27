#ifndef CMD_SYNC_KEY_H
#define CMD_SYNC_KEY_H

#include <cmd-base.h>

class QCmdSyncKey : public QCmdBase
{
  Q_OBJECT

public:
  QCmdSyncKey(bool show, int value = 0);
  ~QCmdSyncKey() Q_DECL_OVERRIDE;

protected:
  void process() Q_DECL_OVERRIDE;

private:
  bool mShow;
  int mValue;
};

#endif /* CMD_SYNC_KEY_H */
