#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QSocketNotifier>
#include <iostream>

class Downloader : public QObject
{
  Q_OBJECT
public:
  explicit Downloader(QObject *parent = nullptr);
  ~Downloader();

private:
  QNetworkAccessManager *m_networkAccess;
  QSocketNotifier *m_notifier;

signals:

public slots:
  void getUrl();
};

#endif // DOWNLOADER_H
