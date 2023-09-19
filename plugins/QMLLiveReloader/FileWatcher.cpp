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

#include "FileWatcher.h"

#include <QFileInfo>
#include <QFileSelector>
#include <QFileSystemWatcher>
#include <QLoggingCategory>
#include <QQmlAbstractUrlInterceptor>
#include <QRegularExpression>
#include <QTimer>
#include <QQuickWindow>
#include <QQmlContext>
#include <QXmlStreamReader>
#include <QDirIterator>

#include <map>

namespace QmlLiveReload {

static Q_LOGGING_CATEGORY(log, "QmlLiveReload::FileWatcher")

void initFileWatcher(QQmlApplicationEngine *engine, const QString& rootSourcePath)
{
    if (engine) {
        if (FileWatcher* ptr = new FileWatcher(engine, rootSourcePath))
        {
            qWarning() << "initFileWatcher";
            ptr->setAutoReload(true);
            engine->rootContext()->setContextProperty("QmlFileWatcher", ptr);
        }
    }
}

class FileWatcherPrivate : QObject//public QQmlAbstractUrlInterceptor
{
    Q_DISABLE_COPY(FileWatcherPrivate)
    Q_DECLARE_PUBLIC(FileWatcher)
    FileWatcher * const q_ptr {nullptr};

    FileWatcherPrivate(FileWatcher* q, QQmlApplicationEngine* _engine, const QString& rootSourcePath) :
        q_ptr(q),
        m_engine(_engine)
    {
        //m_engine->addUrlInterceptor(this);

        QObject::connect(&m_fileWatcher, &QFileSystemWatcher::fileChanged, q_ptr, [&](QString const& path) {
            qCDebug(log) << "File changed:" << path;
            if ( ! autoReload)
                return;

            
            q_ptr->reload(path);

#if defined(Q_OS_WIN) || (defined(Q_OS_UNIX) && !defined(Q_OS_MACOS))
            QTimer::singleShot(500, &m_fileWatcher, [this,path](){
                 m_fileWatcher.addPath(path);
            });
#endif
        });

        QDirIterator it(rootSourcePath, {"*.qml"}, QDir::Files, QDirIterator::Subdirectories);
        
        while (it.hasNext()) {
            QString dir = it.next();
            qDebug() << dir;
            if (!m_fileWatcher.files().contains(dir)) {
                m_fileWatcher.addPath(dir);
            }
        }
    }

    // QUrl intercept(QUrl const& url, QQmlAbstractUrlInterceptor::DataType type) final
    // {
    //     if (type == QQmlAbstractUrlInterceptor::QmlFile) {
    //         m_fileWatcher.addPath(url.path());
    //         qCInfo(log) << QString("Add file to watch: %1").arg(url.path());
    //     }
    //     return url;
    // }

    void reloadQml(QString const& path)
    {
        if (!m_engine) {
            qCDebug(log, "Cannot reload, engine is undefined");
            return;
        }

        qCDebug(log, "Reloading.");

        m_engine->clearComponentCache();

        if (m_engine->rootObjects().isEmpty()) {
            qCWarning(log, "Reloading may have failed! (no root object)");
        }

        qCInfo(log) << QString("Reloaded: %1").arg(path);
        emit q_ptr->reloaded(path);
    }

    QPointer<QQmlApplicationEngine> m_engine;
    QFileSystemWatcher m_fileWatcher;

    bool autoReload {false};
};

FileWatcher::FileWatcher(QQmlApplicationEngine* engine, const QString& rootSourcePath) :
    QObject(engine),
    dd_ptr(new FileWatcherPrivate(this, engine, rootSourcePath))
{}

FileWatcher::~FileWatcher() {}

void FileWatcher::reload(QString const& path)
{
    QMetaObject::invokeMethod(this, "reloadQml", Qt::QueuedConnection, Q_ARG(QString, path));
}

bool FileWatcher::autoReload() const
{
    Q_D(const FileWatcher);
    return d->autoReload;
}

void FileWatcher::setAutoReload(bool autoReload)
{
    Q_D(FileWatcher);
    if (d->autoReload == autoReload)
        return;

    d->autoReload = autoReload;
    emit autoReloadChanged(autoReload);
}

void FileWatcher::reloadQml(QString const& path)
{
    Q_D(FileWatcher);
    d->reloadQml(path);
}

} //namespace LiveReloader


// #include "loaderlive.h"

// #include <QPainter>

// LoaderLive::LoaderLive(QQuickItem *parent)
//     : QQuickPaintedItem(parent)
// {
//     // By default, QQuickItem does not draw anything. If you subclass
//     // QQuickItem to create a visual item, you will need to uncomment the
//     // following line and re-implement updatePaintNode()

//     // setFlag(ItemHasContents, true);
// }

// void LoaderLive::paint(QPainter *painter)
// {
//     QPen pen(QColorConstants::Red, 2);
//     QBrush brush(QColorConstants::Red);

//     painter->setPen(pen);
//     painter->setBrush(brush);
//     painter->drawRect(0, 0, 100, 100);
// }

// LoaderLive::~LoaderLive()
// {
// }
