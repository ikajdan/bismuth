/*
 * SPDX-FileCopyrightText: 2019 Vlad Zahorodnii <vlad.zahorodnii@kde.org>
 * SPDX-FileCopyrightText: 2021 Ignacy Kajdan <git@verahawk.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef MONITOR_H
#define MONITOR_H

#include <QObject>

class MonitorPrivate;

/**
 * The Monitor provides a way for monitoring the state of Bismuth.
 */
class Monitor : public QObject
{
    Q_OBJECT

    /**
     * This property holds a value to indicate if Bismuth is available.
     */
    Q_PROPERTY(bool available READ isAvailable NOTIFY availableChanged)

    /**
     * This property holds a value to indicate currently applied layout.
     */
    Q_PROPERTY(int currentLayout READ currentLayout NOTIFY currentLayoutChanged)

public:
    explicit Monitor(QObject *parent = nullptr);
    ~Monitor() override;

    /**
     * Returns @c true if Bismuth is available; otherwise @c false.
     */
    bool isAvailable() const;

    /**
     * Returns currently applied screen layout.
     */
    int currentLayout() const;

Q_SIGNALS:
    /**
     * This signal is emitted when Bismuth becomes (un)available.
     */
    void availableChanged();

    /**
     * Emitted whenever the current layout has changed.
     */
    void currentLayoutChanged();

private:
    MonitorPrivate *d;
};

#endif // MONITOR_H
