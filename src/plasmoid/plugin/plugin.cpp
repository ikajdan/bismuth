/*
 * SPDX-FileCopyrightText: 2019 Vlad Zahorodnii <vlad.zahorodnii@kde.org>
 * SPDX-FileCopyrightText: 2021 Ignacy Kajdan <git@verahawk.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "plugin.h"
#include "controller.h"
#include "monitor.h"

#include <QQmlEngine>

void BismuthPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(QLatin1String(uri) == QLatin1String("org.kde.plasma.private.bismuth"));
    qmlRegisterType<Controller>(uri, 1, 0, "Controller");
    qmlRegisterType<Monitor>(uri, 1, 0, "Monitor");
}
