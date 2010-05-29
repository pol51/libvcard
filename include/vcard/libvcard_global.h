/**
 *
 * This file is part of the libvcard project.
 *
 * Copyright (C) 2010, Emanuele Bertoldi (Card Tech srl).
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * $Revision$
 * $Date$
 */

#ifndef VCARD_GLOBAL_H
#define VCARD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(VCARD_LIBRARY)
#  define VCARDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define VCARDSHARED_EXPORT Q_DECL_IMPORT
#endif

#define VC_SEPARATOR_TOKEN ';'
#define VC_END_LINE_TOKEN '\n'
#define VC_BEGIN_TOKEN "BEGIN:VCARD"
#define VC_END_TOKEN "END:VCARD"

enum vCardVersion
{
    VC_VER_2_1,
    VC_VER_3_0
};

#endif // VCARD_GLOBAL_H
