#include "rl-controller.h"
#include "cmd-controller.h"

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

  QRlController *const controller = new QRlController();
  QCmdController *const commander = new QCmdController(controller);

  QObject::connect(controller, &QRlController::finished, commander, &QObject::deleteLater);
  QObject::connect(controller, &QRlController::finished, controller, &QObject::deleteLater);
  QObject::connect(controller, &QRlController::finished, &application, &QCoreApplication::quit);
  QObject::connect(controller, &QRlController::command, commander, &QCmdController::onCommand);
  controller->start();

#if 0
  do {
    char *const line = readline(AS_CMD_PROMPT);
    if (!line || !strlen(line)) {
      free(line);
      continue;
    } else if (!strcmp(line, "exit")) {
      free(line);
      break;
    }
    add_history(line);

    /* Cleanup */
    free(line);
  } while (true);
#endif

  const int res = application.exec();

  /* Cleanup */
  free(TheUserName);
  free(TheUserPassword);
  return res;
}
