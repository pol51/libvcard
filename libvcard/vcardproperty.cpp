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

#include "vcardproperty.h"

#define VC_ASSIGNMENT_TOKEN ':'

vCardProperty::vCardProperty()
{
}

vCardProperty::vCardProperty(const QString& name, const QString& value, const vCardParamList& params)
    :   m_name(name),
        m_params(params)
{
    m_values = value.split(VC_SEPARATOR_TOKEN);
}

vCardProperty::vCardProperty(const QString& name, const QStringList& values, const vCardParamList& params)
    :   m_name(name),
        m_values(values),
        m_params(params)
{
}

vCardProperty::vCardProperty(const QString& name, const QString& value, const QString& params)
    :   m_name(name)
{
    m_values = value.split(VC_SEPARATOR_TOKEN);
    m_params = vCardParam::fromByteArray(params.toUtf8());
}

vCardProperty::vCardProperty(const QString& name, const QStringList& values, const QString& params)
    :   m_name(name),
        m_values(values)
{
    m_params = vCardParam::fromByteArray(params.toUtf8());
}

vCardProperty::~vCardProperty()
{
}

QString vCardProperty::name() const
{
    return m_name;
}

QString vCardProperty::value() const
{
    return m_values.join(QString(VC_SEPARATOR_TOKEN));
}

QStringList vCardProperty::values() const
{
    return m_values;
}

vCardParamList vCardProperty::params() const
{
    return m_params;
}

bool vCardProperty::isValid() const
{
    if (m_name.isEmpty())
        return false;

    if (m_values.isEmpty())
        return false;

    foreach (vCardParam param, m_params)
        if (!param.isValid())
            return false;

    return true;
}

bool vCardProperty::operator== (const vCardProperty& prop) const
{
    return ((m_name == prop.name()) && (m_values == prop.values()));
}

bool vCardProperty::operator!= (const vCardProperty& prop) const
{
    return ((m_name != prop.name()) || (m_values != prop.values()));
}

QByteArray vCardProperty::toByteArray(vCardVersion version) const
{
    QByteArray buffer;

    switch (version)
    {
        case VC_VER_2_1:
        case VC_VER_3_0:
        {
            buffer.append(m_name).toUpper();
            if (!m_params.isEmpty())
            {
                buffer.append(VC_SEPARATOR_TOKEN);
                buffer.append(vCardParam::toByteArray(m_params, version));
            }
            buffer.append(QString(VC_ASSIGNMENT_TOKEN));
            buffer.append(m_values.join(QString(VC_SEPARATOR_TOKEN)));
        }
        break;

        default:
            break;
    }

    return buffer;
}

QList<vCardProperty> vCardProperty::fromByteArray(const QByteArray& data)
{
    QList<vCardProperty> properties;

    QStringList lines = QString::fromUtf8(data).split(VC_END_LINE_TOKEN);
    foreach (QString line, lines)
    {
        if (line == VC_BEGIN_TOKEN || line == VC_END_TOKEN)
            break;

        QStringList tokens = line.split(VC_ASSIGNMENT_TOKEN);
        if (tokens.count() >= 2)
        {
            QStringList property_tokens = tokens.at(0).split(VC_SEPARATOR_TOKEN);
            QString name = property_tokens.takeAt(0);
            vCardParamList params = vCardParam::fromByteArray(property_tokens.join(QString(VC_SEPARATOR_TOKEN)).toUtf8());

            properties.append(vCardProperty(name, tokens.at(1), params));
        }
    }

    return properties;
}

vCardProperty vCardProperty::createAddress(const QString& street, const QString& locality, const QString& region, const QString& postal_code, const QString& country, const QString& post_office_box, const QString& ext_address, const vCardParamList& params)
{
    QStringList values;
    values.insert(vCardProperty::PostOfficeBox, post_office_box);
    values.insert(vCardProperty::ExtendedAddress, ext_address);
    values.insert(vCardProperty::Street, street);
    values.insert(vCardProperty::Locality, locality);
    values.insert(vCardProperty::Region, region);
    values.insert(vCardProperty::PostalCode, postal_code);
    values.insert(vCardProperty::Country, country);

    return vCardProperty(VC_ADDRESS, values, params);
}

vCardProperty vCardProperty::createBirthday(const QDate& birthday, const vCardParamList& params)
{
    return vCardProperty(VC_BIRTHDAY, birthday.toString("yyyy-MM-dd"), params);
}

vCardProperty vCardProperty::createBirthday(const QDateTime& birthday, const vCardParamList& params)
{
    return vCardProperty(VC_BIRTHDAY, birthday.toString("yyyy-MM-ddThh:mm:ssZ"), params);
}

vCardProperty vCardProperty::createGeographicPosition(qreal latitude, qreal longitude, const vCardParamList& params)
{
    QStringList values;
    values.insert(vCardProperty::Latitude, QString("%1").arg(latitude));
    values.insert(vCardProperty::Longitude, QString("%1").arg(longitude));

    return vCardProperty(VC_GEOGRAPHIC_POSITION, values, params);
}

vCardProperty vCardProperty::createName(const QString& firstname, const QString& lastname, const QString& additional, const QString& prefix, const QString& suffix, const vCardParamList& params)
{
    QStringList values;
    values.insert(vCardProperty::Lastname, lastname);
    values.insert(vCardProperty::Firstname, firstname);
    values.insert(vCardProperty::Additional, additional);
    values.insert(vCardProperty::Prefix, prefix);
    values.insert(vCardProperty::Suffix, suffix);

    return vCardProperty(VC_NAME, values, params);
}

vCardProperty vCardProperty::createOrganization(const QString& name, const QStringList& levels, const vCardParamList& params)
{
    QStringList values;
    values.append(name);
    values.append(levels);

    return vCardProperty(VC_ORGANIZATION, values, params);
}

