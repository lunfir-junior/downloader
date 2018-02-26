#include <QCoreApplication>
#include <QStringList>

#include "Downloader.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  QStringList arguments = a.arguments();

  arguments.removeFirst();

  if ( arguments.isEmpty() ) {
    qDebug() << "nothing to load";

    return 0;
  }

  Downloader loader;
  loader.append(arguments);

  QObject::connect(&loader, &Downloader::signalFinished, &a, &QCoreApplication::quit);

  a.exec();
}
