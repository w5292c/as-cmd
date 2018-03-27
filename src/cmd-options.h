#ifndef CMD_OPTIONS_H
#define CMD_OPTIONS_H

#include <cmd-base.h>

class QNetworkReply;
class QCmdOptions : public QCmdBase
{
  Q_OBJECT

public:
  QCmdOptions();
  ~QCmdOptions();

protected:
  void process() Q_DECL_OVERRIDE;

protected slots:
  void onRequestFinished();

private:
  QNetworkReply *mReply;
};

#endif /* CMD_OPTIONS_H */
