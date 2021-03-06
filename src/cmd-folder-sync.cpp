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

#include "cmd-folder-sync.h"

#include "as-debug.h"
#include "network-manager.h"

#include <QUrl>
#include <QBuffer>
#include <assert.h>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QProcessEnvironment>
#include <QSslConfiguration>
#include <QAuthenticator>

QCmdFolderSync::QCmdFolderSync() :
  mReply(NULL)
{
  qVerbose(<< "[QCmdFolderSync::QCmdFolderSync]" << this);
}

QCmdFolderSync::~QCmdFolderSync()
{
  qVerbose(<< "[QCmdFolderSync::~QCmdFolderSync]" << this);
}

void QCmdFolderSync::process()
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

  QUrlQuery query;
  query.addQueryItem("Cmd", "FolderSync");
  query.addQueryItem("User", "fakeuser");
  query.addQueryItem("DeviceId", "AsCmdV0100");
  query.addQueryItem("DeviceType", "SmartPhone"); // SmartPhone

  QUrl serverUrl;
  serverUrl.setScheme("https");
  serverUrl.setHost(serverAddress);
  serverUrl.setPort(serverPort.toInt());
  serverUrl.setPath("/Microsoft-Server-ActiveSync");
  serverUrl.setQuery(query);
  qVerbose(<< "[QCmdFolderSync::run] Request URL: " << serverUrl.toString());

  QByteArray requestData;
  // Header
  requestData.append("\x03\x01\x6a\x00", 4);
  // Code page: 7 (folder hierarchy)
  requestData.append("\x00\x07", 2);
  // <FolderSync>
  requestData.append("\x56", 1);
  // <SyncKey>
  requestData.append("\x52\x03", 2);
  // SyncKey value
  requestData.append(QByteArray::number(QAsEnvironment::instance().syncKey()));
  // SyncKey value end-of-string
  requestData.append("\x00", 1);
  // </SyncKey>
  requestData.append("\x01", 1);
  // </FolderSync>
  requestData.append("\x01", 1);

  static QBuffer buffer;
  buffer.setData(requestData);

  QNetworkRequest request;
  request.setUrl(serverUrl);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/vnd.ms-sync.wbxml");
  request.setRawHeader("Connection", "Keep-Alive");
  request.setRawHeader("Host", serverAddress.toUtf8());
  request.setRawHeader("MS-ASProtocolVersion", "14.0");
  const QByteArray &creds = QString("%1:%2").arg(userId).arg(passwd).toUtf8().toBase64();
  const QByteArray &authHeader = QString("Basic %1").arg(creds.constData()).toUtf8();
  request.setRawHeader("Authorization", authHeader);

  mReply = mManager.post(request, &buffer);
  connect(mReply, &QNetworkReply::finished, this, &QCmdFolderSync::onRequestFinished);
}

void QCmdFolderSync::onRequestFinished()
{
  assert(mReply);

  if (QNetworkReply::NoError == mReply->error()) {
    const QByteArray &reply = mReply->readAll();
    dumpWbXml(reply);
  } else {
    qDebug() << "--- Finished with error:" << mReply->error();
  }

  emit done();
}
