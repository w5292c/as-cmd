#ifndef AS_DEBUG
#define AS_DEBUG

#include "as-env.h"
#include <QDebug>

#define qVerbose(...) verbose() && (qDebug() __VA_ARGS__, false)

#endif /* AS_DEBUG */
