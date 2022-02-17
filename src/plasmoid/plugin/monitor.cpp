/*
 * SPDX-FileCopyrightText: 2019 Vlad Zahorodnii <vlad.zahorodnii@kde.org>
 * SPDX-FileCopyrightText: 2021 Ignacy Kajdan <git@verahawk.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "monitor.h"
#include "monitor_p.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDBusServiceWatcher>

static const QString s_serviceName = QStringLiteral("org.kde.KWin");
static const QString s_nightColorPath = QStringLiteral("/ColorCorrect");
static const QString s_nightColorInterface = QStringLiteral("org.kde.kwin.ColorCorrect");
static const QString s_propertiesInterface = QStringLiteral("org.freedesktop.DBus.Properties");

MonitorPrivate::MonitorPrivate(QObject *parent)
    : QObject(parent)
{
    QDBusServiceWatcher *watcher = new QDBusServiceWatcher(s_serviceName, QDBusConnection::sessionBus(), QDBusServiceWatcher::WatchForOwnerChange, this);
    connect(watcher, &QDBusServiceWatcher::serviceRegistered, this, &MonitorPrivate::handleServiceRegistered);
    connect(watcher, &QDBusServiceWatcher::serviceUnregistered, this, &MonitorPrivate::handleServiceUnregistered);

    handleServiceRegistered();
}

MonitorPrivate::~MonitorPrivate()
{
}

void MonitorPrivate::handleServiceRegistered()
{
    QDBusConnection bus = QDBusConnection::sessionBus();

    // clang-format off
    const bool connected = bus.connect(s_serviceName,
                                       s_nightColorPath,
                                       s_propertiesInterface,
                                       QStringLiteral("PropertiesChanged"),
                                       this,
                                       SLOT(handlePropertiesChanged(QString,QVariantMap,QStringList)));
    // clang-format on
    if (!connected) {
        return;
    }

    QDBusMessage message = QDBusMessage::createMethodCall(s_serviceName, s_nightColorPath, s_propertiesInterface, QStringLiteral("GetAll"));
    message.setArguments({s_nightColorInterface});

    QDBusPendingReply<QVariantMap> properties = bus.asyncCall(message);
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(properties, this);

    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *self) {
        self->deleteLater();

        const QDBusPendingReply<QVariantMap> properties = *self;
        if (properties.isError()) {
            return;
        }

        updateProperties(properties.value());
    });
}

void MonitorPrivate::handleServiceUnregistered()
{
    QDBusConnection bus = QDBusConnection::sessionBus();

    // clang-format off
    bus.disconnect(s_serviceName,
                   s_nightColorPath,
                   s_propertiesInterface,
                   QStringLiteral("PropertiesChanged"),
                   this,
                   SLOT(handlePropertiesChanged(QString,QVariantMap,QStringList)));
    // clang-format on

    setAvailable(false);
}

void MonitorPrivate::handlePropertiesChanged(const QString &interfaceName, const QVariantMap &changedProperties, const QStringList &invalidatedProperties)
{
    Q_UNUSED(interfaceName)
    Q_UNUSED(invalidatedProperties)

    updateProperties(changedProperties);
}

int MonitorPrivate::currentLayout() const
{
    return m_currentLayout;
}

void MonitorPrivate::updateProperties(const QVariantMap &properties)
{
    const QVariant available = properties.value(QStringLiteral("available"));
    if (available.isValid()) {
        setAvailable(available.toBool());
    }

    const QVariant currentLayout = properties.value(QStringLiteral("currentLayout"));
    if (currentLayout.isValid()) {
        setCurrentLayout(currentLayout.toInt());
    }
}

void MonitorPrivate::setCurrentLayout(int layout)
{
    if (m_currentLayout == layout) {
        return;
    }
    m_currentLayout = layout;
    Q_EMIT currentLayoutChanged();
}

bool MonitorPrivate::isAvailable() const
{
    return m_isAvailable;
}

void MonitorPrivate::setAvailable(bool available)
{
    if (m_isAvailable == available) {
        return;
    }
    m_isAvailable = available;
    Q_EMIT availableChanged();
}

Monitor::Monitor(QObject *parent)
    : QObject(parent)
    , d(new MonitorPrivate(this))
{
    connect(d, &MonitorPrivate::availableChanged, this, &Monitor::availableChanged);
    connect(d, &MonitorPrivate::currentLayoutChanged, this, &Monitor::currentLayoutChanged);
}

Monitor::~Monitor()
{
}

bool Monitor::isAvailable() const
{
    return d->isAvailable();
}

int Monitor::currentLayout() const
{
    return d->currentLayout();
}
