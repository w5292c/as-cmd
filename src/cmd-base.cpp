#include "cmd-base.h"

#include <QDebug>
#include <QNetworkReply>
#include <QAuthenticator>
#include <QProcessEnvironment>

QCmdBase::QCmdBase()
{
  mManager.moveToThread(this);
  mManager.clearAccessCache();

  connect(&mManager, &QNetworkAccessManager::finished,
          this, &QCmdBase::onRequestReady);
  connect(&mManager, &QNetworkAccessManager::authenticationRequired,
          this, &QCmdBase::authentication);
}

QCmdBase::~QCmdBase()
{
}

void QCmdBase::onRequestReady(QNetworkReply *reply)
{
//  qDebug() << "Done";
//  qDebug() << "Response:" << reply;
  qDebug() << "Error:" << reply->error();
  const QByteArray &body = reply->readAll();
  qDebug() << "Here is the reply:" << body;

  emit finished();
}

void QCmdBase::authentication(QNetworkReply *reply, QAuthenticator *authenticator)
{
//  qDebug() << "Hello";
//  qDebug() << "[QCmdBase::authentication]: " << reply << ", " << authenticator;

  const QProcessEnvironment &env = QProcessEnvironment::systemEnvironment();
  const QString &userId = env.value("MY_USER", "<user>");
  const QString &passwd = env.value("MY_PASS", "<password>");
  qDebug() << "Here is it:" << userId << "," << passwd;
  authenticator->setUser(userId);
  authenticator->setPassword(passwd);
}
