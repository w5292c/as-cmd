#include <QDebug>
#include <readline.h>
#include <history.h>
#include <QCoreApplication>

#define AS_CMD_PROMPT "AS >>> "

namespace {
void showHelp();
}

int main(int argc, char **argv)
{
  QCoreApplication application(argc, argv);
  qDebug() << "Starting application";

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

  qDebug() << "About to exit application";
  return 0;
}

namespace {
void showHelp()
{
  qDebug() << ">>> help - Show help";
  qDebug() << ">>> exit - Exit the application";
}

}
