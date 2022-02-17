# SPDX-FileCopyrightText: 2021 Ignacy Kajdan <git@verahawk.com>
# SPDX-License-Identifier: MIT

set(
  bismuthplugin_SOURCES
  controller.cpp
  monitor.cpp
  plugin.cpp
)

add_library(bismuthplugin SHARED ${bismuthplugin_SOURCES})

target_link_libraries(
  bismuthplugin
  Qt::Core
  Qt::DBus
  Qt::Gui
  Qt::Qml
)

install(FILES qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/plasma/private/bismuth)
install(TARGETS bismuthplugin DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/plasma/private/bismuth)
