#include "as-env.h"

#include <as-debug.h>

#include <assert.h>

static bool TheVerbose = false;
static QAsEnvironment *TheAsEnvironment = NULL;

void QAsEnvironment::init(QObject *parent)
{
  assert(!TheAsEnvironment);

  TheAsEnvironment = new QAsEnvironment(parent);
}

QAsEnvironment &QAsEnvironment::instance()
{
  assert(TheAsEnvironment);

  return *TheAsEnvironment;
}

QAsEnvironment::QAsEnvironment(QObject *parent) :
  QObject(parent),
  mSyncKey(0)
{
  qVerbose(<< "[QAsEnvironment::QAsEnvironment]" << TheAsEnvironment);
}

QAsEnvironment::~QAsEnvironment()
{
  qVerbose(<< "[QAsEnvironment::~QAsEnvironment]" << this);
}

bool verbose()
{
  return TheVerbose;
}

void setVerbose(bool enable)
{
  TheVerbose = enable;
}

int QAsEnvironment::syncKey() const
{
  return mSyncKey;
}

void QAsEnvironment::setSyncKey(int key)
{
  mSyncKey = key;
}
