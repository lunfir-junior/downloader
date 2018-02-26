#include "Downloader.h"

Downloader::Downloader(QObject *parent) : QObject(parent)
{
  m_networkAccess = new QNetworkAccessManager(this);
  m_notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);

  connect(m_notifier, &QSocketNotifier::activated, this, &Downloader::getUrl);
}

Downloader::~Downloader()
{
  delete m_networkAccess;
}

void Downloader::getUrl()
{
  qDebug() << "in getUrl slot";

  std::string line;
//  QString tmp;
  QUrl url;

  std::getline(std::cin, line);
//  tmp = QString
  url = QUrl(QString::fromStdString(line));

  qDebug() << "url: " << url;
}
