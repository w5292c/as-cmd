#ifndef CMD_OPTIONS_H
#define CMD_OPTIONS_H

#include <cmd-base.h>

class QNetworkReply;
class QCmdOptions : public QCmdBase
{
  Q_OBJECT

public:
  QCmdOptions();

protected:
  void run() Q_DECL_OVERRIDE;

private:
  QNetworkReply *mReply;
};

#endif /* CMD_OPTIONS_H */
