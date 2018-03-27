#include "network-manager.h"

#include "as-debug.h"

#include <assert.h>

static QNetworkManager *TheNetworkManager = NULL;

void QNetworkManager::init(QObject *parent)
{
  assert(!TheNetworkManager);
  TheNetworkManager = new QNetworkManager(parent);
}

QNetworkManager &QNetworkManager::instance()
{
  assert(TheNetworkManager);
  return *TheNetworkManager;
}

QNetworkManager::QNetworkManager(QObject *parent) : QObject(parent)
{
  qVerbose(<< "[QNetworkManager::QNetworkManager]" << this);
}

QNetworkManager::~QNetworkManager()
{
  qVerbose(<< "[QNetworkManager::~QNetworkManager]" << this);
}
