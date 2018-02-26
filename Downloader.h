#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QtCore>
#include <QtNetwork>
#include <QTextStream>

class Downloader : public QObject
{
  Q_OBJECT
public:
  explicit Downloader(QObject *parent = nullptr);
  ~Downloader();

//  void append(const QStringList &urls);
  void append(const QUrl &url);
  void append(const QStringList &urls);
  static QString getFileName(const QUrl &url);

private:
  QNetworkAccessManager m_manager;
  QQueue<QUrl> m_downloadQueue;
  QNetworkReply *m_currentDownload;
  QFile m_file;

signals:
  void signalFinished();

public slots:
  void startNextDownload();
  void downloadFinished();
  void downloadReadyRead();
};

#endif // DOWNLOADER_H
