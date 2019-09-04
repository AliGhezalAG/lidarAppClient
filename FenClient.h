#ifndef HEADER_FENCLIENT
#define HEADER_FENCLIENT

#include <QtWidgets>
#include <QtNetwork>
#include <QObject>
#include "ui_FenClient.h"
#include "zonepacket.h"
#include "objectpacket.h"


class FenClient : public QWidget, private Ui::FenClient
{
    Q_OBJECT

public:
    FenClient();

private slots:
    void on_boutonConnexion_clicked();
    void on_boutonRequest_clicked();
    void donneesRecues();
    void connecte();
    void deconnecte();
    void erreurSocket(QAbstractSocket::SocketError erreur);

private:
    QTcpSocket *zoneSocket;
    QTcpSocket *objectSocket;
    quint16 tailleMessage;
    void processZones(QList<Zone> &zoneList);
    ZonePacket zonePacket;
    ObjectPacket objectPacket;
    QList<Zone> zoneList;
    QVariantMap getMapFromStream(QByteArray &stream);

signals:
    void countingProcessingEnded();
};

#endif
