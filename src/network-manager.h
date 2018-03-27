#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <QObject>
#include <QNetworkAccessManager>

class QNetworkManager : public QObject
{
public:
  static void init(QObject *parent);
  static QNetworkManager &instance();
   ~QNetworkManager() Q_DECL_OVERRIDE;

  inline QNetworkAccessManager &manager() { return mManager; }

private:
  QNetworkManager(QObject *parent);

private:
  QNetworkAccessManager mManager;
};

#endif /* NETWORK_MANAGER_H */
