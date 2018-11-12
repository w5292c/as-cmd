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

#include "cmd-sign.h"

#include "as-debug.h"

#include <QFile>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <QCryptographicHash>

QCmdSign::QCmdSign()
{
  qVerbose(<< "[QCmdSign::QCmdSign]" << this);
}

QCmdSign::~QCmdSign()
{
  qVerbose(<< "[QCmdSign::~QCmdSign]" << this);
}

void QCmdSign::process()
{
  const QVariant &filename = QAsEnvironment::instance().property("filename");
  if (filename.isNull()) {
    qWarning() << "Error: the property 'filename' is not defined, cannot continue";
    emit done();
    return;
  }

  const QString &rsaFilenameString = QAsEnvironment::instance().property("rsa").toString();
  if (rsaFilenameString.isEmpty()) {
    qWarning() << "Error: the property 'rsa' is not defined, cannot continue";
    emit done();
    return;
  }

  const QString &filenameString = filename.toString();
  qVerbose(<< "[QCmdSign::process] Filename: " << filenameString);
  if (!QFile::exists(filenameString)) {
    qWarning() << "Error: " << filenameString << " does not exist";
    emit done();
    return;
  }
  qVerbose(<< "[QCmdSign::process] RSA key filename: " << rsaFilenameString);
  if (!QFile::exists(rsaFilenameString)) {
    qWarning() << "Error: " << rsaFilenameString << " does not exist";
    emit done();
    return;
  }

  QFile file(filenameString);
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning() << "Error: failed to open" << filenameString;
    emit done();
    return;
  }

  qint64 read;
  char buffer[1024];
  QCryptographicHash hash(QCryptographicHash::Sha256);
  do {
    read = file.read(buffer, sizeof (buffer));
    if (read <= 0) {
      break;
    }

    hash.addData(buffer, read);
  } while (true);

  FILE *const rsaFile = fopen(rsaFilenameString.toUtf8().data(), "r");
  if (!rsaFile) {
    qWarning() << "Error: failed to open" << rsaFilenameString;
    emit done();
    return;
  }

  RSA *const rsa = PEM_read_RSAPrivateKey(rsaFile, NULL, NULL, NULL);
  fclose(rsaFile);
  if (!rsa) {
    qWarning() << "Error: failed to parse the input PEM file \"../data/rsa.pem\"";
    emit done();
    return;
  }

  const int rsaLength = RSA_size(rsa);
  if (rsaLength <= 0 || rsaLength > 1024) {
    qWarning() << "Error: wrong RSA size:" << rsaLength;
    RSA_free(rsa);
    emit done();
    return;
  }
  qVerbose(<< "[QCmdSign::process] RSA size:" << rsaLength);

  char rsaOutput[1024];
  const QByteArray &hashResult = hash.result();
  qDebug() << "The hash of the file is:" << hashResult.toHex();
  const int rsaResult = RSA_private_encrypt(hashResult.length(), (const unsigned char *)hashResult.data(), (unsigned char *)rsaOutput, rsa, RSA_PKCS1_PADDING);
  if (rsaResult < 0) {
    qWarning() << "Error: RSA algorithm failed";
    RSA_free(rsa);
    emit done();
    return;
  }

  const QByteArray &result = QByteArray::fromRawData((const char *)rsaOutput, rsaResult);
  qDebug() << "RSA result: length:" << rsaResult << ", value:" << result.toHex();

  RSA_free(rsa);

  emit done();
}
