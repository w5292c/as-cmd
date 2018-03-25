#ifndef CMD_OPTIONS_H
#define CMD_OPTIONS_H

#include <QObject>

class QCmdOptions : public QObject
{
  Q_OBJECT

public:
  QCmdOptions();

public slots:
  void execute();

};

#endif /* CMD_OPTIONS_H */
