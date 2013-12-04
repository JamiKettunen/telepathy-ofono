/*
 * Copyright (C) 2013 Canonical, Ltd.
 *
 * Authors:
 *  Tiago Salem Herrmann <tiago.herrmann@canonical.com>
 *
 * This file is part of telepathy-ofono.
 *
 * telepathy-ofono is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * telepathy-ofono is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef VOICECALLMANAGERPRIVATE_H
#define VOICECALLMANAGERPRIVATE_H

#include <QDBusContext>
#include <QDBusObjectPath>
#include "mock_common.h"

class OfonoVoiceCall;

class VoiceCallManagerPrivate : public QObject, protected QDBusContext {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.ofono.VoiceCallManager")
public:
    VoiceCallManagerPrivate(QObject *parent = 0);
    ~VoiceCallManagerPrivate();
Q_SIGNALS:
    void CallRemoved(const QDBusObjectPath &obj);
    void CallAdded(const QDBusObjectPath &obj, const QVariantMap &value);
    void PropertyChanged(const QString &name, const QDBusVariant &value);
    void TonesReceived(const QString &tones);
private Q_SLOTS:
    void onVoiceCallDestroyed();
public Q_SLOTS:
    QVariantMap GetProperties();
    void SetProperty(const QString &name, const QDBusVariant &value);
    QDBusObjectPath MockIncomingCall(const QString &from);
    QDBusObjectPath Dial(const QString &to, const QString &hideCallerId);
    QMap<QDBusObjectPath, QVariantMap> GetCalls();
    void SwapCalls();
    void SendTones(const QString &tones);
private:
    QVariantMap mProperties;
    QMap<QString, OfonoVoiceCall*> mVoiceCalls;
    int voiceCallCount;
};

extern QMap<QString, VoiceCallManagerPrivate*> voiceCallManagerData;

#endif
