#include "network-manager.h"

#include <assert.h>

static QNetworkManager *object = NULL;

void QNetworkManager::init(QObject *parent)
{
  assert(!object);
  object = new QNetworkManager(parent);
}

QNetworkManager &QNetworkManager::instance()
{
  assert(object);
  return *object;
}

QNetworkManager::QNetworkManager(QObject *parent) : QObject(parent)
{
}
