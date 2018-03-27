#include "cmd-sync-key.h"

#include "as-env.h"

#include "as-debug.h"

QCmdSyncKey::QCmdSyncKey(bool show, int value) :
  mShow(show),
  mValue(value)
{
  qVerbose(<< "[QCmdSyncKey::QCmdSyncKey]" << this);
}

QCmdSyncKey::~QCmdSyncKey()
{
  qVerbose(<< "[QCmdSyncKey::~QCmdSyncKey]" << this);
}

void QCmdSyncKey::process()
{
  if (mShow) {
    qDebug() << ">>> SyncKey:" << QAsEnvironment::instance().syncKey();
  } else {
    QAsEnvironment::instance().setSyncKey(mValue);
    qDebug() << ">>> SyncKey:" << QAsEnvironment::instance().syncKey();
  }

  emit done();
}
