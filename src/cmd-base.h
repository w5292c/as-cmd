#ifndef CMD_BASE_H
#define CMD_BASE_H

#include <QThread>
#include <QNetworkAccessManager>

class QCmdBase : public QThread
{
  Q_OBJECT

public:
  QCmdBase();
  ~QCmdBase();

public slots:
  void onRequestReady(QNetworkReply *reply);
  void authentication(QNetworkReply *reply, QAuthenticator *authenticator);

signals:
  void started();
  void finished();

protected:
  QNetworkAccessManager mManager;
};

#endif /* CMD_BASE_H */
