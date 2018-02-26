#include "Downloader.h"


Downloader::Downloader(QObject *parent) : QObject(parent)
{
  m_currentDownload = nullptr;
}

Downloader::~Downloader()
{

}

void Downloader::append(const QStringList &urls)
{
  for (const QString &urlAsString : urls)
    append(QUrl::fromEncoded(urlAsString.toLocal8Bit()));

  if ( m_downloadQueue.isEmpty() )
    QTimer::singleShot(0, this, &Downloader::signalFinished);
}

void Downloader::append(const QUrl &url)
{
  if ( m_downloadQueue.isEmpty() )
      QTimer::singleShot(0, this, &Downloader::startNextDownload);

  m_downloadQueue.enqueue(url);
}

QString Downloader::getFileName(const QUrl &url)
{
  QString path = url.path();
  QString filename = QFileInfo(path).fileName();

  if ( QFile::exists(filename) )
      qDebug() << "Alert. File overwriting.";

  return filename;
}

void Downloader::startNextDownload()
{
  QUrl url;
  QString filename;
  QNetworkRequest request;

  if ( m_downloadQueue.isEmpty() ) {
    qDebug() << "download complete";
    emit signalFinished();

    return;
  }

  url = m_downloadQueue.dequeue();
  filename = getFileName(url);

  m_file.setFileName(filename);

  if ( !m_file.open(QIODevice::WriteOnly) ) {
    qDebug() << "file save error: " << m_file.errorString();

    return;
  }

  request = QNetworkRequest(url);
  m_currentDownload = m_manager.get(request);

  connect(m_currentDownload, &QNetworkReply::finished,  this, &Downloader::downloadFinished);
  connect(m_currentDownload, &QNetworkReply::readyRead, this, &Downloader::downloadReadyRead);
}

void Downloader::downloadFinished()
{
  m_file.close();

  if ( m_currentDownload->error() ) {
    qDebug() << "download error";
    m_file.remove();
  }

  startNextDownload();
}

void Downloader::downloadReadyRead()
{
    m_file.write(m_currentDownload->readAll());
}


