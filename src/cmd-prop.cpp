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

#include "cmd-prop.h"

#include "as-env.h"
#include "as-debug.h"

#include <QMetaProperty>

QCmdProp::QCmdProp(bool showList, const QString &name, bool show, const QString &value) :
  mShow(show),
  mShowList(showList),
  mName(name),
  mValue(value)
{
  qVerbose(<< "[QCmdProp::QCmdProp]" << this);
}

QCmdProp::~QCmdProp()
{
  qVerbose(<< "[QCmdProp::~QCmdProp]" << this);
}

void QCmdProp::process()
{
  if (mShowList) {
    const QMetaObject *const metaObject = QAsEnvironment::instance().metaObject();
    QList<QByteArray> propNames;
    const int n = metaObject->propertyCount();
    for (int i = 0; i < n; ++i) {
      const QMetaProperty &metaProp = metaObject->property(i);
      propNames.append(metaProp.name());
    }
    propNames.append(QAsEnvironment::instance().dynamicPropertyNames());

    qDebug() << "Properties:" << propNames;
  }
  else if (mShow) {
    qDebug() << "[" << mName << "]:" << QAsEnvironment::instance().property(mName.toUtf8());
  } else {
    const QByteArray &key = mName.toUtf8();

    // Convert the value
    bool ok = false;
    const int intValue = mValue.toInt(&ok);

    QVariant value;
    if (ok) {
      value = QVariant(intValue);
    } else if (mValue == "true" || mValue == "false") {
      value = QVariant((mValue == "true") ? true : false);
    } else {
      value = mValue;
    }
    qVerbose(<< "New value:" << value);
    QAsEnvironment::instance().setProperty(key, value);
    qDebug() << "[" << mName << "]:" << QAsEnvironment::instance().property(key);
  }

  emit done();
}
