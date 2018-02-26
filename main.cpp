#include <QCoreApplication>
#include "Downloader.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  Downloader loader;

  return a.exec();
}
