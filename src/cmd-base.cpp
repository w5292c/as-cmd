/*
 * MIT License
 *
 * Copyright (c) 2018 Alexander Chumakov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
  WB_UTINY *pXml = NULL;
  WB_ULONG xmlLength = 0;
  const WBXMLError wbres = wbxml_conv_wbxml2xml_withlen(
    (unsigned char *)wbxml.constData(), wbxml.length(),
    &pXml, &xmlLength,
    &params);
  qDebug("WBXML Dump, convertion result: %d, length: %d:", wbres, xmlLength);
  if (!wbres) {
    for (WB_ULONG i = 0; i < xmlLength; ++i) {
      if (!pXml[i]) {
        pXml[i] = '?';
      }
    }
    qDebug() << (const char *)pXml;
  } else {
    qDebug() << "Length:" << wbxml.length();
    qDebug() << wbxml.toHex();
  }
}
