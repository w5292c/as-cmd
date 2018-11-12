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

#ifndef AS_ENV_H
#define AS_ENV_H

#include <QObject>

class QAsEnvironment : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int syncKey READ syncKey WRITE setSyncKey)
  Q_PROPERTY(QString filename READ filename WRITE setFilename)
  Q_PROPERTY(int collectionId READ collectionId WRITE setCollectionId)
  Q_PROPERTY(QString rsa READ rsa WRITE setRsa)

public:
  ~QAsEnvironment() Q_DECL_OVERRIDE;
  static void init(QObject *parent);
  static QAsEnvironment &instance();

  int syncKey() const;
  void setSyncKey(int key);
  int collectionId() const;
  void setCollectionId(int value);
  QString rsa() const;
  void setRsa(const QString &rsa);
  QString filename() const;
  void setFilename(const QString &filename);

private:
  QAsEnvironment(QObject *parent);

private:
  int mSyncKey;
  int mCollectionId;
  QString mFilename;
  QString mRsaFilename;
};

bool verbose();
void setVerbose(bool enable);

#endif /* AS_ENV_H */
