#include "cmd-base.h"

#include "as-debug.h"

#include <QNetworkReply>
#include <QAuthenticator>
#include <QProcessEnvironment>

QCmdBase::QCmdBase()
{
  qVerbose(<< "[QCmdBase::QCmdBase]" << this);

  mManager.moveToThread(this);
  mManager.clearAccessCache();

  connect(&mManager, &QNetworkAccessManager::authenticationRequired,
          this, &QCmdBase::authentication);
  connect(this, &QCmdBase::done, this, &QCmdBase::quit);
  connect(this, &QCmdBase::finished, this, &QCmdBase::deleteLater);
}

QCmdBase::~QCmdBase()
{
  qVerbose(<< "[QCmdBase::~QCmdBase]" << this);
}

void QCmdBase::run()
{
  process();

  qVerbose(<< "[QCmdBase::run] Enter the event loop");
  exec();
  qVerbose(<< "[QCmdBase::run] Done with the event loop");
}

void QCmdBase::authentication(QNetworkReply *reply, QAuthenticator *authenticator)
{
  (void)reply;

  const QProcessEnvironment &env = QProcessEnvironment::systemEnvironment();
  const QString &userId = env.value("MY_USER", "<user>");
  const QString &passwd = env.value("MY_PASS", "<password>");
  authenticator->setUser(userId);
  authenticator->setPassword(passwd);
}
