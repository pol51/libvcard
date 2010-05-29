##
# This file is part of the libvcard project.
#
# Copyright (C) 2010, Emanuele Bertoldi (Card Tech srl).
#
# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by the
# Free Software Foundation, either version 3 of the License, or (at your
# option) any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
# more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>
#
# $Revision$
# $Date$
##

VERSION=1.0.0
VCARD_INCDIR = include/vcard
VCARD_SRCDIR = libvcard

PUBLIC_HEADERS = $$VCARD_INCDIR/libvcard_global.h \
    $$VCARD_INCDIR/vcard.h \
    $$VCARD_INCDIR/vcardproperty.h \
    $$VCARD_INCDIR/vcardparam.h

QT -= gui
TARGET = vcard
TEMPLATE = lib
DEFINES += VCARD_LIBRARY
INCLUDEPATH += $$VCARD_INCDIR
HEADERS += $$PUBLIC_HEADERS
SOURCES += $$VCARD_SRCDIR/vcard.cpp \
    $$VCARD_SRCDIR/vcardproperty.cpp \
    $$VCARD_SRCDIR/vcardparam.cpp
DESTDIR = $$VCARD_LIBDIR

unix: {
    # install library and headers
    isEmpty(PREFIX) {
      PREFIX = /usr/local
    }
    target.path = $$PREFIX/lib
    INSTALLS += target

    incfiles.path = $$PREFIX/include/vcard
    incfiles.files = $$PUBLIC_HEADERS
    INSTALLS += incfiles

    # install pkg-config file (libvcard.pc)
    CONFIG += create_pc create_prl
    QMAKE_PKGCONFIG_REQUIRES = QtCore
    QMAKE_PKGCONFIG_LIBDIR = $$target.path
    QMAKE_PKGCONFIG_INCDIR = $$incfiles.path
    QMAKE_PKGCONFIG_DESTDIR = pkgconfig
}
