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

#ifndef VCARDPARAM_H
#define VCARDPARAM_H

#include "libvcard_global.h"
#include <QtCore/QString>

class VCARDSHARED_EXPORT vCardParam
{
public:
    enum vCardParamGroup
    {
        Type,
        Encoding,
        Charset,
        Undefined
    };

protected:
    vCardParamGroup m_group;
    QString m_value;

public:
    vCardParam();
    vCardParam(const QString& value, vCardParamGroup group = vCardParam::Undefined);
    ~vCardParam();

    vCardParamGroup group() const;
    QString value() const;
    bool isValid() const;

    bool operator== (const vCardParam& param) const;
    bool operator!= (const vCardParam& param) const;

    QByteArray toByteArray(vCardVersion version = VC_VER_2_1) const;

    static QByteArray toByteArray(QList<vCardParam> params, vCardVersion version = VC_VER_2_1);
    static QList<vCardParam> fromByteArray(const QByteArray& data);
};

typedef QList<vCardParam> vCardParamList;

#endif // VCARDPARAM_H
