#include "cmd-options.h"

#include "network-manager.h"

#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QProcessEnvironment>
#include <QSslConfiguration>
#include <QAuthenticator>

QCmdOptions::QCmdOptions() :
  mReply(NULL)
{
}

void QCmdOptions::run()
{
  if (mReply) {
    qDebug() << "Error: OPTIONS is busy";
    emit finished();
    return;
  }

  const QProcessEnvironment &env = QProcessEnvironment::systemEnvironment();
  const QString &serverAddress = env.value("MY_ADDR", "exchange-server.com");
  const QString &serverPort = env.value("MY_PORT", "443");
  const QUrl &serverUrl = QUrl(QLatin1String("https://") + serverAddress + ":" + serverPort + "/Microsoft-Server-ActiveSync");
  qDebug() << "[QCmdOptions::run] URL: " << serverUrl;

    QNetworkRequest request(serverUrl);
//    request.setHeader(QNetworkRequest::UserAgentHeader, "curl/7.35.0");
//    request.setRawHeader("Host", "mobile.ur.ch:443");
    request.setRawHeader("Proxy-Connection", "Keep-Alive");
    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(sslConfig);

//  connect(&mManager, &QNetworkAccessManager::finished,
//          this, &QCmdBase::onRequestReady);
//  connect(&mManager, &QNetworkAccessManager::authenticationRequired,
//          this, &QCmdBase::authentication);

  mReply = mManager.sendCustomRequest(request, "OPTIONS");
//  connect(mReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(finished()));
//  connect(mReply, &QNetworkReply::finished, this, &QCmdOptions::finished);
//  connect(mReply, &QNetworkReply::sslErrors, this, &QCmdOptions::finished);
//    connect(mReply, SIGNAL(finished()), this, SLOT(onOptionsRequestReady()));
//    connect(mReply, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(onSslErrors(QList<QSslError>)));

//  emit finished();
  exec();
}
