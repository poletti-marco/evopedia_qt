/*
 * evopedia: An offline Wikipedia reader.
 *
 * Copyright (C) 2010-2011 evopedia developers
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "evopediaapplication.h"

#include <QTranslator>
#include <QLibraryInfo>

#include "utils.h"

EvopediaApplication::EvopediaApplication(int &argc, char **argv) :
#if defined(NO_GUI)
    QCoreApplication(argc, argv)
#else
    QApplication(argc, argv)
#endif
{
#if defined(Q_WS_X11) && !defined(NO_GUI)
    QApplication::setGraphicsSystem("raster");
#endif

    QTranslator *qtTranslator = new QTranslator(this);
    qtTranslator->load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    installTranslator(qtTranslator);

    qtTranslator = new QTranslator(this);
    qtTranslator->load(":tr/evopedia_" + QLocale::system().name());
    installTranslator(qtTranslator);

    bool guiEnabled = !arguments().contains("--server-only");
#if defined(NO_GUI)
    guiEnabled = false;
#endif
    m_evopedia = new Evopedia(this, guiEnabled);

    if (m_evopedia->isGUIEnabled()) {
        m_mainwindow = new MainWindow();

#if !defined(NO_GUI)
#if defined(Q_WS_S60)
        m_mainwindow->showMaximized();
#else
        m_mainwindow->show();
#endif
#endif
    } else {
        m_mainwindow = 0;
        connect(m_evopedia->findChild<EvopediaWebServer *>("evopediaWebserver"),
                SIGNAL(applicationExitRequested()), SLOT(quit()));
    }
}

EvopediaApplication::~EvopediaApplication()
{
    delete m_evopedia;
    delete m_mainwindow;
}

int main(int argc, char *argv[])
{
    /* initialize random number generator */
    randomNumber(2);

    EvopediaApplication app(argc, argv);
    return app.exec();
}
