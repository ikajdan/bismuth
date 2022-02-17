/*
 * SPDX-FileCopyrightText: 2019 Vlad Zahorodnii <vlad.zahorodnii@kde.org>
 * SPDX-FileCopyrightText: 2021 Ignacy Kajdan <git@verahawk.com>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller() override;

    // HACK
//     enum Layout {
//         tile,
//         monocle,
//         column,
//         spiral,
//         spread,
//         stair,
//         quarter,
//         floating
//     };
//     Q_ENUM(Layout)

    QVector<QString> Layout {
        "tile",
        "monocle",
        "three_column",
        "spiral",
        "spread",
        "stair",
        "quarter",
        "float"
    };

public Q_SLOTS:
    void toggle_layout(const QString id);
    void next_layout();
    void prev_layout();
};

#endif // CONTROLLER_H
