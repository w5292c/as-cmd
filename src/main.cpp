/*
 * MIT License
 *
 * Copyright (c) 2018 Alexander Chumakov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
