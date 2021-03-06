/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

// checksum 0x17fa version 0x3000a
/*
  This file was generated by the Qt Quick Application wizard of Qt Creator.
  QmlApplicationViewer is a convenience class containing mobile device specific
  code such as screen orientation handling. Also QML paths and debugging are
  handled here.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/

#include "qmlapplicationviewer.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtDeclarative/QDeclarativeComponent>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeContext>

#if defined(QMLJSDEBUGGER)
#include <qt_private/qdeclarativedebughelper_p.h>
#endif

#if defined(QMLJSDEBUGGER) && !defined(NO_JSDEBUGGER)
#include <jsdebuggeragent.h>
#endif
#if defined(QMLJSDEBUGGER) && !defined(NO_QMLOBSERVER)
#include <qdeclarativeviewobserver.h>
#endif

#if defined(QMLJSDEBUGGER)

// Enable debugging before any QDeclarativeEngine is created
struct QmlJsDebuggingEnabler
{
    QmlJsDebuggingEnabler()
    {
        QDeclarativeDebugHelper::enableDebugging();
    }
};

// Execute code in constructor before first QDeclarativeEngine is instantiated
static QmlJsDebuggingEnabler enableDebuggingHelper;

#endif // QMLJSDEBUGGER

class QmlApplicationViewerPrivate
{
    QString mainQmlFile;
    friend class QmlApplicationViewer;
    static QString adjustPath(const QString &path);
};

QString QmlApplicationViewerPrivate::adjustPath(const QString &path)
{
#ifdef Q_OS_UNIX
#ifdef Q_OS_MAC
    if (!QDir::isAbsolutePath(path))
        return QCoreApplication::applicationDirPath()
                + QLatin1String("/../Resources/") + path;
#else
    const QString pathInShareDir = QCoreApplication::applicationDirPath()
        + QLatin1String("/../share/")
        + QFileInfo(QCoreApplication::applicationFilePath()).fileName()
        + QLatin1Char('/') + path;
    if (QFileInfo(pathInShareDir).exists())
        return pathInShareDir;
#endif
#endif
    return path;
}

QmlApplicationViewer::QmlApplicationViewer(QWidget *parent) :
    QDeclarativeView(parent),
    m_d(new QmlApplicationViewerPrivate)
{
    connect(engine(), SIGNAL(quit()), SLOT(close()));
    setResizeMode(QDeclarativeView::SizeRootObjectToView);
#if defined(QMLJSDEBUGGER) && !defined(NO_JSDEBUGGER)
    new QmlJSDebugger::JSDebuggerAgent(engine());
#endif
#if defined(QMLJSDEBUGGER) && !defined(NO_QMLOBSERVER)
    new QmlJSDebugger::QDeclarativeViewObserver(this, parent);
#endif
}

QmlApplicationViewer::~QmlApplicationViewer()
{
    delete m_d;
}

void QmlApplicationViewer::setMainQmlFile(const QString &file)
{
    m_d->mainQmlFile = QmlApplicationViewerPrivate::adjustPath(file);
    setSource(QUrl::fromLocalFile(m_d->mainQmlFile));
}

void QmlApplicationViewer::addImportPath(const QString &path)
{
    engine()->addImportPath(QmlApplicationViewerPrivate::adjustPath(path));
}

void QmlApplicationViewer::setOrientation(ScreenOrientation orientation)
{
//#if defined(Q_OS_SYMBIAN)
//    // If the version of Qt on the device is < 4.7.2, that attribute won't work
//    if (orientation != ScreenOrientationAuto) {
//        const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
//        if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
//            qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
//            return;
//        }
//    }
//#endif // Q_OS_SYMBIAN
//
//    Qt::WidgetAttribute attribute;
//    switch (orientation) {
//#if QT_VERSION < 0x040702
//    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
//    case ScreenOrientationLockPortrait:
//        attribute = static_cast<Qt::WidgetAttribute>(128);
//        break;
//    case ScreenOrientationLockLandscape:
//        attribute = static_cast<Qt::WidgetAttribute>(129);
//        break;
//    default:
//    case ScreenOrientationAuto:
//        attribute = static_cast<Qt::WidgetAttribute>(130);
//        break;
//#else // QT_VERSION < 0x040702
//    case ScreenOrientationLockPortrait:
//        attribute = Qt::WA_LockPortraitOrientation;
//        break;
//    case ScreenOrientationLockLandscape:
//        attribute = Qt::WA_LockLandscapeOrientation;
//        break;
//    default:
//    case ScreenOrientationAuto:
//        attribute = Qt::WA_AutoOrientation;
//        break;
//#endif // QT_VERSION < 0x040702
//    };
//    setAttribute(attribute, true);
}

void QmlApplicationViewer::showExpanded()
{
#ifdef Q_OS_SYMBIAN
    showFullScreen();
#elif defined(Q_WS_MAEMO_5) || defined(Q_WS_MAEMO_6)
    showMaximized();
#else
    show();
#endif
}
