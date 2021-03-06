// The MIT License (MIT)
//
// Copyright (c) Itay Grudev 2015 - 2020
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

//
//  W A R N I N G !!!
//  -----------------
//
// This file is not part of the KiranSingleApplication API. It is used purely as an
// implementation detail. This header file may change from version to
// version without notice, or may even be removed.
//

#include <cstdlib>
#include <cstddef>

#include <QtCore/QDir>
#include <QtCore/QThread>
#include <QtCore/QByteArray>
#include <QtCore/QDataStream>
#include <QtCore/QElapsedTimer>
#include <QtCore/QCryptographicHash>
#include <QtNetwork/QLocalServer>
#include <QtNetwork/QLocalSocket>

#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
#include <QtCore/QRandomGenerator>
#else
#include <QtCore/QDateTime>
#endif

#include "kiran-single-application.h"
#include "kiran-single-application_p.h"

#ifdef Q_OS_UNIX
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

#ifdef Q_OS_WIN
#ifndef NOMINMAX
        #define NOMINMAX 1
    #endif
    #include <windows.h>
    #include <lmcons.h>
#endif

KiranSingleApplicationPrivate::KiranSingleApplicationPrivate(KiranSingleApplication *q_ptr )
    : q_ptr( q_ptr )
{
    server = nullptr;
    socket = nullptr;
    memory = nullptr;
    instanceNumber = 0;
}

KiranSingleApplicationPrivate::~KiranSingleApplicationPrivate()
{
    if( socket != nullptr ){
        socket->close();
        delete socket;
    }

    if( memory != nullptr ){
        memory->lock();
        auto *inst = static_cast<InstancesInfo*>(memory->data());
        if( server != nullptr ){
            server->close();
            delete server;
            inst->primary = false;
            inst->primaryPid = -1;
            inst->primaryUser[0] =  '\0';
            inst->checksum = blockChecksum();
        }
        memory->unlock();

        delete memory;
    }
}

QString KiranSingleApplicationPrivate::getUsername()
{
#ifdef Q_OS_WIN
    wchar_t username[UNLEN + 1];
      // Specifies size of the buffer on input
      DWORD usernameLength = UNLEN + 1;
      if( GetUserNameW( username, &usernameLength ) )
          return QString::fromWCharArray( username );
#if QT_VERSION < QT_VERSION_CHECK(5, 10, 0)
      return QString::fromLocal8Bit( qgetenv( "USERNAME" ) );
#else
      return qEnvironmentVariable( "USERNAME" );
#endif
#endif
#ifdef Q_OS_UNIX
    QString username;
    uid_t uid = geteuid();
    struct passwd *pw = getpwuid( uid );
    if( pw )
        username = QString::fromLocal8Bit( pw->pw_name );
    if ( username.isEmpty() ){
#if QT_VERSION < QT_VERSION_CHECK(5, 10, 0)
        username = QString::fromLocal8Bit( qgetenv( "USER" ) );
#else
        username = qEnvironmentVariable( "USER" );
#endif
    }
    return username;
#endif
}

void KiranSingleApplicationPrivate::genBlockServerName()
{
    QCryptographicHash appData( QCryptographicHash::Sha256 );
    appData.addData( "KiranSingleApplication", 17 );
    appData.addData(KiranSingleApplication::app_t::applicationName().toUtf8() );
    appData.addData(KiranSingleApplication::app_t::organizationName().toUtf8() );
    appData.addData(KiranSingleApplication::app_t::organizationDomain().toUtf8() );

    if ( ! appDataList.isEmpty() )
        appData.addData( appDataList.join( "" ).toUtf8() );

    if( ! (options & KiranSingleApplication::Mode::ExcludeAppVersion) ){
        appData.addData(KiranSingleApplication::app_t::applicationVersion().toUtf8() );
    }

    if( ! (options & KiranSingleApplication::Mode::ExcludeAppPath) ){
#ifdef Q_OS_WIN
        appData.addData( KiranSingleApplication::app_t::applicationFilePath().toLower().toUtf8() );
#else
        appData.addData(KiranSingleApplication::app_t::applicationFilePath().toUtf8() );
#endif
    }

    // User level block requires a user specific data in the hash
    if( options & KiranSingleApplication::Mode::User ){
        appData.addData( getUsername().toUtf8() );
    }

    // Replace the backslash in RFC 2045 Base64 [a-zA-Z0-9+/=] to comply with
    // server naming requirements.
    blockServerName = appData.result().toBase64().replace("/", "_");
}

void KiranSingleApplicationPrivate::initializeMemoryBlock() const
{
    auto *inst = static_cast<InstancesInfo*>( memory->data() );
    inst->primary = false;
    inst->secondary = 0;
    inst->primaryPid = -1;
    inst->primaryUser[0] =  '\0';
    inst->checksum = blockChecksum();
}

void KiranSingleApplicationPrivate::startPrimary()
{
    // Reset the number of connections
    auto *inst = static_cast <InstancesInfo*>( memory->data() );

    inst->primary = true;
    inst->primaryPid = QCoreApplication::applicationPid();
    qstrncpy( inst->primaryUser, getUsername().toUtf8().data(), sizeof(inst->primaryUser) );
    inst->checksum = blockChecksum();
    instanceNumber = 0;
    // Successful creation means that no main process exists
    // So we start a QLocalServer to listen for connections
    QLocalServer::removeServer( blockServerName );
    server = new QLocalServer();

    // Restrict access to the socket according to the
    // KiranSingleApplication::Mode::User flag on User level or no restrictions
    if( options & KiranSingleApplication::Mode::User ){
        server->setSocketOptions( QLocalServer::UserAccessOption );
    } else {
        server->setSocketOptions( QLocalServer::WorldAccessOption );
    }

    server->listen( blockServerName );
    QObject::connect(
        server,
        &QLocalServer::newConnection,
        this,
        &KiranSingleApplicationPrivate::slotConnectionEstablished
    );
}

void KiranSingleApplicationPrivate::startSecondary()
{
    auto *inst = static_cast <InstancesInfo*>( memory->data() );

    inst->secondary += 1;
    inst->checksum = blockChecksum();
    instanceNumber = inst->secondary;
}

bool KiranSingleApplicationPrivate::connectToPrimary( int msecs, ConnectionType connectionType )
{
    QElapsedTimer time;
    time.start();

    // Connect to the Local Server of the Primary Instance if not already
    // connected.
    if( socket == nullptr ){
        socket = new QLocalSocket();
    }

    if( socket->state() == QLocalSocket::ConnectedState ) return true;

    if( socket->state() != QLocalSocket::ConnectedState ){

        while( true ){
            randomSleep();

            if( socket->state() != QLocalSocket::ConnectingState )
                socket->connectToServer( blockServerName );

            if( socket->state() == QLocalSocket::ConnectingState ){
                socket->waitForConnected( static_cast<int>(msecs - time.elapsed()) );
            }

            // If connected break out of the loop
            if( socket->state() == QLocalSocket::ConnectedState ) break;

            // If elapsed time since start is longer than the method timeout return
            if( time.elapsed() >= msecs ) return false;
        }
    }

    // Initialisation message according to the KiranSingleApplication protocol
    QByteArray initMsg;
    QDataStream writeStream(&initMsg, QIODevice::WriteOnly);

#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    writeStream.setVersion(QDataStream::Qt_5_6);
#endif

    writeStream << blockServerName.toLatin1();
    writeStream << static_cast<quint8>(connectionType);
    writeStream << instanceNumber;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    quint16 checksum = qChecksum(QByteArray(initMsg, static_cast<quint32>(initMsg.length())));
#else
    quint16 checksum = qChecksum(initMsg.constData(), static_cast<quint32>(initMsg.length()));
#endif
    writeStream << checksum;

    // The header indicates the message length that follows
    QByteArray header;
    QDataStream headerStream(&header, QIODevice::WriteOnly);

#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    headerStream.setVersion(QDataStream::Qt_5_6);
#endif
    headerStream << static_cast <quint64>( initMsg.length() );

    socket->write( header );
    socket->write( initMsg );
    bool result = socket->waitForBytesWritten( static_cast<int>(msecs - time.elapsed()) );
    socket->flush();
    return result;
}

quint16 KiranSingleApplicationPrivate::blockChecksum() const
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    quint16 checksum = qChecksum(QByteArray(static_cast<const char*>(memory->constData()), offsetof(InstancesInfo, checksum)));
#else
    quint16 checksum = qChecksum(static_cast<const char*>(memory->constData()), offsetof(InstancesInfo, checksum));
#endif
    return checksum;
}

qint64 KiranSingleApplicationPrivate::primaryPid() const
{
    qint64 pid;

    memory->lock();
    auto *inst = static_cast<InstancesInfo*>( memory->data() );
    pid = inst->primaryPid;
    memory->unlock();

    return pid;
}

QString KiranSingleApplicationPrivate::primaryUser() const
{
    QByteArray username;

    memory->lock();
    auto *inst = static_cast<InstancesInfo*>( memory->data() );
    username = inst->primaryUser;
    memory->unlock();

    return QString::fromUtf8( username );
}

/**
 * @brief Executed when a connection has been made to the LocalServer
 */
void KiranSingleApplicationPrivate::slotConnectionEstablished()
{
    QLocalSocket *nextConnSocket = server->nextPendingConnection();
    connectionMap.insert(nextConnSocket, ConnectionInfo());

    QObject::connect(nextConnSocket, &QLocalSocket::aboutToClose, this,
                     [nextConnSocket, this](){
                       auto &info = connectionMap[nextConnSocket];
                       this->slotClientConnectionClosed( nextConnSocket, info.instanceId );
                     }
    );

    QObject::connect(nextConnSocket, &QLocalSocket::disconnected, nextConnSocket, &QLocalSocket::deleteLater);

    QObject::connect(nextConnSocket, &QLocalSocket::destroyed, this,
                     [nextConnSocket, this](){
                       connectionMap.remove(nextConnSocket);
                     }
    );

    QObject::connect(nextConnSocket, &QLocalSocket::readyRead, this,
                     [nextConnSocket, this](){
                       auto &info = connectionMap[nextConnSocket];
                       switch(info.stage){
                       case StageHeader:
                           readInitMessageHeader(nextConnSocket);
                           break;
                       case StageBody:
                           readInitMessageBody(nextConnSocket);
                           break;
                       case StageConnected:
                           this->slotDataAvailable( nextConnSocket, info.instanceId );
                           break;
                       default:
                           break;
                       };
                     }
    );
}

void KiranSingleApplicationPrivate::readInitMessageHeader( QLocalSocket *sock )
{
    if (!connectionMap.contains( sock )){
        return;
    }

    if( sock->bytesAvailable() < ( qint64 )sizeof( quint64 ) ){
        return;
    }

    QDataStream headerStream( sock );

#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    headerStream.setVersion( QDataStream::Qt_5_6 );
#endif

    // Read the header to know the message length
    quint64 msgLen = 0;
    headerStream >> msgLen;
    ConnectionInfo &info = connectionMap[sock];
    info.stage = StageBody;
    info.msgLen = msgLen;

    if ( sock->bytesAvailable() >= (qint64) msgLen ){
        readInitMessageBody( sock );
    }
}

void KiranSingleApplicationPrivate::readInitMessageBody( QLocalSocket *sock )
{
    Q_Q(KiranSingleApplication);

    if (!connectionMap.contains( sock )){
        return;
    }

    ConnectionInfo &info = connectionMap[sock];
    if( sock->bytesAvailable() < ( qint64 )info.msgLen ){
        return;
    }

    // Read the message body
    QByteArray msgBytes = sock->read(info.msgLen);
    QDataStream readStream(msgBytes);

#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    readStream.setVersion( QDataStream::Qt_5_6 );
#endif

    // server name
    QByteArray latin1Name;
    readStream >> latin1Name;

    // connection type
    ConnectionType connectionType = InvalidConnection;
    quint8 connTypeVal = InvalidConnection;
    readStream >> connTypeVal;
    connectionType = static_cast <ConnectionType>( connTypeVal );

    // instance id
    quint32 instanceId = 0;
    readStream >> instanceId;

    // checksum
    quint16 msgChecksum = 0;
    readStream >> msgChecksum;

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    const quint16 actualChecksum = qChecksum(QByteArray(msgBytes, static_cast<quint32>(msgBytes.length() - sizeof(quint16))));
#else
    const quint16 actualChecksum = qChecksum(msgBytes.constData(), static_cast<quint32>(msgBytes.length() - sizeof(quint16)));
#endif

    bool isValid = readStream.status() == QDataStream::Ok &&
        QLatin1String(latin1Name) == blockServerName &&
        msgChecksum == actualChecksum;

    if( !isValid ){
        sock->close();
        return;
    }

    info.instanceId = instanceId;
    info.stage = StageConnected;

    if( connectionType == NewInstance ||
        ( connectionType == SecondaryInstance &&
            options & KiranSingleApplication::Mode::SecondaryNotification ) )
    {
        Q_EMIT q->instanceStarted();
    }

    if (sock->bytesAvailable() > 0){
        this->slotDataAvailable( sock, instanceId );
    }
}

void KiranSingleApplicationPrivate::slotDataAvailable( QLocalSocket *dataSocket, quint32 instanceId )
{
    Q_Q(KiranSingleApplication);
    Q_EMIT q->receivedMessage( instanceId, dataSocket->readAll() );
}

void KiranSingleApplicationPrivate::slotClientConnectionClosed( QLocalSocket *closedSocket, quint32 instanceId )
{
    if( closedSocket->bytesAvailable() > 0 )
        slotDataAvailable( closedSocket, instanceId  );
}

void KiranSingleApplicationPrivate::randomSleep()
{
#if QT_VERSION >= QT_VERSION_CHECK( 5, 10, 0 )
    QThread::msleep( QRandomGenerator::global()->bounded( 8u, 18u ));
#else
    qsrand( QDateTime::currentMSecsSinceEpoch() % std::numeric_limits<uint>::max() );
    QThread::msleep( qrand() % 11 + 8);
#endif
}

void KiranSingleApplicationPrivate::addAppData(const QString &data)
{
    appDataList.push_back(data);
}

QStringList KiranSingleApplicationPrivate::appData() const
{
    return appDataList;
}