/*
 * SPDX-FileCopyrightText: 2019 Vlad Zahorodnii <vlad.zahorodnii@kde.org>
 * SPDX-FileCopyrightText: 2021 Ignacy Kajdan <git@verahawk.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef MONITOR_P_H
#define MONITOR_P_H

#include <QObject>

class MonitorPrivate : public QObject
{
    Q_OBJECT

public:
    explicit MonitorPrivate(QObject *parent = nullptr);
    ~MonitorPrivate() override;

    int currentLayout() const;
    bool isAvailable() const;

Q_SIGNALS:
    void currentLayoutChanged();
    void availableChanged();

private Q_SLOTS:
    void handleServiceRegistered();
    void handleServiceUnregistered();
    void handlePropertiesChanged(const QString &interfaceName, const QVariantMap &changedProperties, const QStringList &invalidatedProperties);

private:
    void updateProperties(const QVariantMap &properties);
    void setCurrentLayout(int temperature);
    void setAvailable(bool available);

    int m_currentLayout = 0;
    bool m_isAvailable = false;
};

#endif // MONITOR_P_H
