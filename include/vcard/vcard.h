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

#ifndef VCARD_H
#define VCARD_H

#include "vcardproperty.h"

class VCARDSHARED_EXPORT vCard
{
protected:
    vCardPropertyList m_properties;

public:
    vCard();
    vCard(const vCard& vcard);
    vCard(const vCardPropertyList& properties);
    virtual ~vCard();
    
    void addProperty(const vCardProperty& property);
    void removeProperty(const vCardProperty& property);
    void addProperties(const vCardPropertyList& properties);
    vCardPropertyList properties() const;
    vCardProperty property(const QString& name, const vCardParamList& params = vCardParamList(), bool strict = false) const;
    bool contains(const QString& property, const vCardParamList& params = vCardParamList(), bool strict = false) const;
    bool contains(const vCardProperty& property) const;
    bool isValid() const;
    
    int count() const;
    QByteArray toByteArray(vCardVersion version = VC_VER_2_1) const;
    
    bool saveToFile(const QString& filename) const;
    
    static QList<vCard> fromByteArray(const QByteArray& data);
    static QList<vCard> fromFile(const QString& filename);
};

typedef QList<vCard> vCardList;

#endif // VCARD_H
