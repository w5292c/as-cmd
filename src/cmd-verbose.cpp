#include "cmd-verbose.h"

#include "as-env.h"

#include "as-debug.h"

QCmdVerbose::QCmdVerbose(bool show, bool on) :
  mOn(on),
  mShow(show)
{
  qVerbose(<< "[QCmdVerbose::QCmdVerbose]" << this);
}

QCmdVerbose::~QCmdVerbose()
{
  qVerbose(<< "[QCmdVerbose::~QCmdVerbose]" << this);
}

void QCmdVerbose::process()
{
  if (mShow) {
    qDebug() << ">>> Verbose:" << (verbose() ? "ON" : "OFF");
  } else {
    setVerbose(mOn);
    qDebug() << ">>> Verbose:" << (verbose() ? "ON" : "OFF");
  }

  emit done();
}
