#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSocketNotifier>
#include <QFile>
#include <QString>
#include <iostream>

class Downloader : public QObject
{
  Q_OBJECT
public:
  explicit Downloader(QObject *parent = nullptr);
  ~Downloader();

private:
  QNetworkAccessManager *m_manager;
  QNetworkReply *m_download;
  QSocketNotifier *m_notifier;
//  QFile m_file;
  QString m_filename;

//  bool saveFile();

signals:
  void signalCanStartDownload(const QUrl &url);
  void signalCanProcessDownload(/*QNetworkReply *reply*/);

public slots:
  void getUrl();
  void startDownload(const QUrl &url);
  void processDownload();
  void finishDownload();
};

#endif // DOWNLOADER_H
