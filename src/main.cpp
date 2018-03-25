#include "rl-controller.h"
#include "cmd-controller.h"

#include <QDebug>
#include <QCoreApplication>

namespace {
char *TheUserName = NULL;
char *TheUserPassword = NULL;

void showHelp();
}

int main(int argc, char **argv)
{
  QCoreApplication application(argc, argv);
  qDebug() << "Starting application";

  QCmdController *const commander = new QCmdController();

  QRlController *const controller = new QRlController();
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

    if (!strcmp(line, "help")) {
      showHelp();
      free(line);
      continue;
    }

    /* Debug output */
    qDebug("Here is the user input: \"%s\"", line);

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

namespace {
void showHelp()
{
  qDebug() << ">>> help - Show help";
  qDebug() << ">>> exit - Exit the application";
}

}
