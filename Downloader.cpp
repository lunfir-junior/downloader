#include "Downloader.h"

Downloader::Downloader(QObject *parent) : QObject(parent)
{
  m_manager = new QNetworkAccessManager(this);
  m_notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
  m_download = nullptr;

  connect(m_notifier, &QSocketNotifier::activated, this, &Downloader::getUrl);

  connect(this, &Downloader::signalCanStartDownload, this, &Downloader::startDownload);
  connect(this, &Downloader::signalCanProcessDownload, this, &Downloader::processDownload);
}

Downloader::~Downloader()
{
  delete m_manager;
}

void Downloader::getUrl()
{
  qDebug() << "in getUrl slot";

  std::string line;
  QString tmp;
  QUrl url;

  std::getline(std::cin, line);
  tmp = QString::fromStdString(line);
  url = QUrl(tmp);
  m_filename = tmp.split('/', QString::SkipEmptyParts, Qt::CaseSensitive).takeLast();
  qDebug() << "m_filename: " << m_filename;

  emit signalCanStartDownload(url);
}

void Downloader::startDownload(const QUrl &url)
{
  qDebug() << "in startDownload slot";
  qDebug() << url;

  QNetworkRequest request = QNetworkRequest(url);

  m_download = m_manager->get(request);

  emit signalCanProcessDownload(/*m_download*/);
}

void Downloader::processDownload(/*QNetworkReply *reply*/)
{
  qDebug() << "in processDownload slot";
  QUrl url = m_download->url();
  qDebug() << url;

  QFile m_file(m_filename);

    if (!m_file.open(QIODevice::WriteOnly)) {
        fprintf(stderr, "Could not open %s for writing: %s\n",
                qPrintable(m_filename),
                qPrintable(m_file.errorString()));
//        return false;
    }

    m_file.write(m_download->readAll());
    m_file.close();

//    return true;

}

void Downloader::finishDownload()
{

}
