/*
Copyright (c) 2007, Trenton Schulz

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

 3. The name of the author may not be used to endorse or promote products
    derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef BONJOURSERVICERESOLVER_H
#define BONJOURSERVICERESOLVER_H

#include <QtCore/QObject>

#ifndef AVAHI_COMPAT_DNS_SD
#include <dns_sd.h>
#else
#include <avahi-compat-libdns_sd/dns_sd.h>
#endif
class QSocketNotifier;
class QHostInfo;
class BonjourRecord;

class BonjourServiceResolver : public QObject
{
	Q_OBJECT
public:
    BonjourServiceResolver(QObject *parent);
    ~BonjourServiceResolver() override;

    bool resolveBonjourRecord(const BonjourRecord &record);

signals:
    void bonjourRecordResolved(const QHostInfo &hostInfo, int port);
    void error(DNSServiceErrorType error);

private slots:
    void bonjourSocketReadyRead();
    void cleanupResolve();
    void finishConnect(const QHostInfo &hostInfo);

private:
    static void DNSSD_API bonjourResolveReply(DNSServiceRef sdRef, DNSServiceFlags flags,
                                    quint32 interfaceIndex, DNSServiceErrorType errorCode,
                                    const char *fullName, const char *hosttarget, quint16 port,
                                    quint16 txtLen, const char *txtRecord, void *context);
    DNSServiceRef dnssref;
    QSocketNotifier *bonjourSocket;
    int bonjourPort;
};

#endif // BONJOURSERVICERESOLVER_H
