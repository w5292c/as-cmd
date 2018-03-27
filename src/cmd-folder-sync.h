#ifndef CMD_FOLDER_SYNC_H
#define CMD_FOLDER_SYNC_H

#include <cmd-base.h>

class QNetworkReply;
class QCmdFolderSync : public QCmdBase
{
  Q_OBJECT

public:
  QCmdFolderSync();
  ~QCmdFolderSync() Q_DECL_OVERRIDE;

protected:
  void process() Q_DECL_OVERRIDE;

protected slots:
  void onRequestFinished();

private:
  QNetworkReply *mReply;
};

#endif /* CMD_FOLDER_SYNC_H */
