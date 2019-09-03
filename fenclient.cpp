
#include "FenClient.h"

FenClient::FenClient()
{
    setupUi(this);

    zoneSocket = new QTcpSocket(this);
    objectSocket = new QTcpSocket(this);
    //connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    //connect(socket, &QIODevice::readyRead, this, &FenClient::donneesRecues);
    connect(zoneSocket, SIGNAL(connected()), this, SLOT(connecte()));
    connect(zoneSocket, SIGNAL(disconnected()), this, SLOT(deconnecte()));
    connect(zoneSocket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(zoneSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));

    connect(objectSocket, SIGNAL(connected()), this, SLOT(connecte()));
    connect(objectSocket, SIGNAL(disconnected()), this, SLOT(deconnecte()));
//    connect(objectSocket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(objectSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));

    tailleMessage = 0;
    zoneList = {};
}

// Tentative de connexion au serveur
void FenClient::on_boutonConnexion_clicked()
{
    // On annonce sur la fenêtre qu'on est en train de se connecter
    listeMessages->append(tr("<em>Tentative de connexion en cours...</em>"));
    boutonConnexion->setEnabled(false);

    zoneSocket->abort(); // On désactive les connexions précédentes s'il y en a
    zoneSocket->connectToHost(serveurIP->text(), 17172); // On se connecte au serveur demandé
    objectSocket->abort(); // On désactive les connexions précédentes s'il y en a
    objectSocket->connectToHost(serveurIP->text(), 17171); // On se connecte au serveur demandé
}

// Envoi d'un message au serveur
void FenClient::on_boutonRequest_clicked()
{
    while(true){
        {
            QEventLoop loop;
            qInfo() << "start of loop";
            loop.connect(this, SIGNAL(countingProcessingEnded()), SLOT(quit()), Qt::QueuedConnection);
            donneesRecues();
            loop.exec();
        }
        qInfo() << "end of loop";
    }

}

// On a reçu un paquet (ou un sous-paquet)
void FenClient::donneesRecues()
{
    QByteArray zoneStreamSeparator = QByteArray::fromHex("0000");
    QByteArray objectStreamSeparator = QByteArray::fromHex("0000");

    QByteArray zoneStream = zoneSocket->readAll();
    QByteArray objectStream = objectSocket->readAll();

    int startIndex = zoneStream.indexOf(zoneStreamSeparator)+2;
    int endIndex = zoneStream.indexOf(zoneStreamSeparator, startIndex)-2;
    QByteArray packet = zoneStream.mid(startIndex, endIndex-startIndex);
    //    listeMessages->append(QTextCodec::codecForMib(106)->toUnicode(packet));

    QJsonDocument jsonPacket = QJsonDocument::fromJson(packet);
    QJsonObject root_obj = jsonPacket.object();
    QVariantMap root_map = root_obj.toVariantMap();

    ZonePacket zonePack = *new ZonePacket(root_map);


    startIndex = zoneStream.indexOf(objectStreamSeparator)+2;
    endIndex = zoneStream.indexOf(objectStreamSeparator, startIndex)-2;
    packet = zoneStream.mid(startIndex, endIndex-startIndex);
    //    listeMessages->append(QTextCodec::codecForMib(106)->toUnicode(packet));

    jsonPacket = QJsonDocument::fromJson(packet);
    root_obj = jsonPacket.object();
    root_map = root_obj.toVariantMap();

    ObjectPacket objectPack = *new ObjectPacket(root_map);

//    QVariant header_map = root_map["header"].toMap();
//    QVariantList zone_map = root_map["zones"].toList();

//    zoneList.clear();
//    QVariant currentZone;
//    for (int i = 0; i < zone_map.size(); i++) {
//        currentZone = zone_map.at(i);
//        QVariantMap zone_map = currentZone.value<QVariantMap>();
//        Zone myZone = *new Zone(zone_map["name"].toString(), zone_map["objectCount"].toInt(), zone_map["objectIds"].value<QList<int>>());
//        Zone testZone = *new Zone(zone_map);
//        zoneList.append(myZone);
//        objectCount->setText(QString::number(myZone.objectCount));
//        emit countingProcessingEnded();
//    }
}

void FenClient::processZones(QList<Zone> &zoneList)
{

}

// Ce slot est appelé lorsque la connexion au serveur a réussi
void FenClient::connecte()
{
    listeMessages->append(tr("<em>Connexion réussie !</em>"));
    boutonConnexion->setEnabled(true);
}

// Ce slot est appelé lorsqu'on est déconnecté du serveur
void FenClient::deconnecte()
{
    listeMessages->append(tr("<em>Déconnecté du serveur</em>"));
}

// Ce slot est appelé lorsqu'il y a une erreur
void FenClient::erreurSocket(QAbstractSocket::SocketError erreur)
{
    switch(erreur) // On affiche un message différent selon l'erreur qu'on nous indique
    {
    case QAbstractSocket::HostNotFoundError:
        listeMessages->append(tr("<em>ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.</em>"));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        listeMessages->append(tr("<em>ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.</em>"));
        break;
    case QAbstractSocket::RemoteHostClosedError:
        listeMessages->append(tr("<em>ERREUR : le serveur a coupé la connexion.</em>"));
        break;
    default:
        listeMessages->append(tr("<em>ERREUR : ") + erreur + tr("</em>"));
    }

    boutonConnexion->setEnabled(true);
}
