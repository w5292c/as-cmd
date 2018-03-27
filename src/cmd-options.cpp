#include "cmd-options.h"

#include "network-manager.h"

#include <QUrl>
#include <assert.h>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QProcessEnvironment>
#include <QSslConfiguration>
#include <QAuthenticator>

QCmdOptions::QCmdOptions() :
  mReply(NULL)
{
}

QCmdOptions::~QCmdOptions()
{
}

void QCmdOptions::process()
{
  if (mReply) {
    qDebug() << "Error: OPTIONS is busy";
    emit done();
    return;
  }

  const QProcessEnvironment &env = QProcessEnvironment::systemEnvironment();
  const QString &userId = env.value("MY_USER", "<user>");
  const QString &serverPort = env.value("MY_PORT", "443");
  const QString &passwd = env.value("MY_PASS", "<password>");
  const QString &serverAddress = env.value("MY_ADDR", "exchange-server.com");
  QUrl serverUrl;
  serverUrl.setScheme("https");
  serverUrl.setHost(serverAddress);
  serverUrl.setPort(serverPort.toInt());
  serverUrl.setPath("/Microsoft-Server-ActiveSync");
  qDebug() << "[QCmdOptions::run] Request URL: " << serverUrl.toString();

  QNetworkRequest request;
  request.setUrl(serverUrl);
  request.setRawHeader("Connection", "Keep-Alive");
  request.setRawHeader("Host", serverAddress.toUtf8());
  const QByteArray &creds = QString("%1:%2").arg(userId).arg(passwd).toUtf8().toBase64();
  const QByteArray &authHeader = QString("Basic %1").arg(creds.constData()).toUtf8();
  request.setRawHeader("Authorization", authHeader);

  mReply = mManager.sendCustomRequest(request, "OPTIONS");
  connect(mReply, &QNetworkReply::finished, this, &QCmdOptions::onRequestFinished);
}

void QCmdOptions::onRequestFinished()
{
  assert(mReply);

  if (QNetworkReply::NoError == mReply->error()) {
    const QByteArray &protoVersions = mReply->rawHeader("MS-ASProtocolVersions");
    const QByteArray &protoCommands = mReply->rawHeader("MS-ASProtocolCommands");
    qDebug() << "--- Supported protocol versions:" << protoVersions;
    qDebug() << "--- Supported protocol commands:" << protoCommands;
  } else {
    qDebug() << "--- Finished with error:" << mReply->error();
  }

  emit done();
}
