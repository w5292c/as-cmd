#include <QDebug>
#include <QCoreApplication>

int main(int argc, char **argv)
{
  QCoreApplication application(argc, argv);
  qDebug() << "Starting application";

  qDebug() << "About to exit application";
  return 0;
}
