/*
 * SPDX-FileCopyrightText: 2019 Vlad Zahorodnii <vlad.zahorodnii@kde.org>
 * SPDX-FileCopyrightText: 2021 Ignacy Kajdan <git@verahawk.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "controller.h"

#include <QDBusConnection>
#include <QDBusMessage>

static const QString s_serviceName = QStringLiteral("org.kde.kglobalaccel");
static const QString s_path = QStringLiteral("/component/bismuth");
static const QString s_interface = QStringLiteral("org.kde.kglobalaccel.Component");

Controller::Controller(QObject *parent)
    : QObject(parent)
{
}

Controller::~Controller()
{
}

void Controller::toggle_layout(const QString id)
{
    QDBusMessage message = QDBusMessage::createMethodCall(s_serviceName, s_path, s_interface, QStringLiteral("invokeShortcut"));
    message.setArguments({QStringLiteral("toggle_") + Layout[id.toInt()] + QStringLiteral("_layout")});

    QDBusConnection::sessionBus().send(message);
}

void Controller::next_layout()
{
    QDBusMessage message = QDBusMessage::createMethodCall(s_serviceName, s_path, s_interface, QStringLiteral("invokeShortcut"));
    message.setArguments({QStringLiteral("next_layout")});

    QDBusConnection::sessionBus().send(message);
}

void Controller::prev_layout()
{
    QDBusMessage message = QDBusMessage::createMethodCall(s_serviceName, s_path, s_interface, QStringLiteral("invokeShortcut"));
    message.setArguments({QStringLiteral("prev_layout")});

    QDBusConnection::sessionBus().send(message);
}
