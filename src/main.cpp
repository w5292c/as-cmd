#include "as-env.h"
#include "rl-controller.h"
#include "cmd-controller.h"
#include "network-manager.h"

#include <QDebug>
#include <QCoreApplication>

namespace {
char *TheUserName = NULL;
char *TheUserPassword = NULL;
}

int main(int argc, char **argv)
{
  QCoreApplication application(argc, argv);
  qDebug() << "Starting application";

  /* Check 'verbose' argument first */
  int i;
  for (i = 1; i < argc; ++i) {
    if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--verbose")) {
      setVerbose(true);
      break;
    }
  }

  QAsEnvironment::init(&application);
  QNetworkManager::init(&application);
  QRlController *const controller = new QRlController();
  QCmdController *const commander = new QCmdController(controller);

  QObject::connect(controller, &QRlController::finished, commander, &QObject::deleteLater);
  QObject::connect(controller, &QRlController::finished, controller, &QObject::deleteLater);
  QObject::connect(controller, &QRlController::finished, &application, &QCoreApplication::quit);
  QObject::connect(controller, &QRlController::command, commander, &QCmdController::onCommand);
  controller->start();

  const int res = application.exec();

  /* Cleanup */
  free(TheUserName);
  free(TheUserPassword);
  return res;
}
