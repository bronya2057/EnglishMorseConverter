/*
* Copyright (c) 2019, Benjamin Balga
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include <QObject>
#include <QQmlApplicationEngine>
#include <QScopedPointer>
#include <QtQml/qqmlregistration.h>

namespace QmlLiveReload {

void initFileWatcher(QQmlApplicationEngine* engine, const QString& rootSourcePath);

class FileWatcherPrivate;
class FileWatcher : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool autoReload READ autoReload WRITE setAutoReload NOTIFY autoReloadChanged)
    QML_ELEMENT
    QML_UNCREATABLE("Can't create FileWatcher as type")

public:
    explicit FileWatcher(QQmlApplicationEngine* engine, const QString& rootSourcePath);
    ~FileWatcher() override;

    bool autoReload() const;
    void setAutoReload(bool autoReload);

signals:
    void autoReloadChanged(bool autoReload);
    void reloaded(const QString path);

private slots:
    void reloadQml(QString const& path);

private:
    void reload(QString const& path);

    Q_DECLARE_PRIVATE_D(dd_ptr, FileWatcher)
    QScopedPointer<FileWatcherPrivate> dd_ptr;
};

} //namespace QmlLiveReload


// #ifndef LOADERLIVE_H
// #define LOADERLIVE_H

// #include <QtQuick/QQuickPaintedItem>

// class LoaderLive : public QQuickPaintedItem
// {
//     Q_OBJECT
//     QML_ELEMENT
//     Q_DISABLE_COPY(LoaderLive)
// public:
//     explicit LoaderLive(QQuickItem *parent = nullptr);
//     void paint(QPainter *painter) override;
//     ~LoaderLive() override;
// };

// #endif // LOADERLIVE_H
