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

#include "cmd-options.h"

#include "as-debug.h"
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
  qVerbose(<< "[QCmdOptions::QCmdOptions]" << this);
}

QCmdOptions::~QCmdOptions()
{
  qVerbose(<< "[QCmdOptions::~QCmdOptions]" << this);
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
  qVerbose(<< "[QCmdOptions::run] Request URL: " << serverUrl.toString());

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
