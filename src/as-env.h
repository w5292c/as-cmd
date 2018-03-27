#ifndef AS_ENV_H
#define AS_ENV_H

#include <QObject>

class QAsEnvironment : public QObject
{
  Q_OBJECT

public:
  ~QAsEnvironment() Q_DECL_OVERRIDE;
  static void init(QObject *parent);
  static QAsEnvironment &instance();

private:
  QAsEnvironment(QObject *parent);

private:
};

bool verbose();
void setVerbose(bool enable);

#endif /* AS_ENV_H */
