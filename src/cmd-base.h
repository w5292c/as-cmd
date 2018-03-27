#ifndef CMD_BASE_H
#define CMD_BASE_H

#include <QThread>
#include <QNetworkAccessManager>

class QCmdBase : public QThread
{
  Q_OBJECT

public:
  QCmdBase();
  ~QCmdBase() Q_DECL_OVERRIDE;

public slots:
  void authentication(QNetworkReply *reply, QAuthenticator *authenticator);

signals:
  void done();

protected:
  virtual void process() = 0;
  void run() Q_DECL_OVERRIDE;
  void dumpWbXml(const QByteArray &wbxml);

protected:
  QNetworkAccessManager mManager;
};

#endif /* CMD_BASE_H */
