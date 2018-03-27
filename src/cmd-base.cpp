#include "cmd-base.h"

#include "as-debug.h"

#include <wbxml.h>
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

void QCmdBase::dumpWbXml(const QByteArray &wbxml)
{
  WBXMLGenXMLParams params;
  params.gen_type = WBXML_GEN_XML_INDENT;
  params.lang = WBXML_LANG_AIRSYNC;
  params.indent = 0;
  params.keep_ignorable_ws = TRUE;
  WB_ULONG xmlLength = 2;
  WB_UTINY *pXml = NULL;
  const WBXMLError wbres = wbxml_conv_wbxml2xml_withlen(
    (unsigned char *)wbxml.constData(), wbxml.length(),
    &pXml, &xmlLength,
    &params);
  qDebug("WBXML Dump, convertion result: %d, length: %d:", wbres, xmlLength);
  qDebug() << (const char *)pXml;
}
