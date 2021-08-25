/**
 *
 * This file is part of the libvcard project.
 *
 * Copyright (C) 2010, Emanuele Bertoldi (Card Tech srl).
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * $Revision$
 * $Date$
 */

#ifndef VCARD_H
#define VCARD_H

#include "vcardproperty.h"

class vCard
{
protected:
    vCardPropertyList m_properties;

public:
    vCard();
    vCard(const vCard& vcard);
    vCard(const vCardPropertyList& properties);
    virtual ~vCard();

    void addProperty(const vCardProperty& property);
    void removeProperties(const QString& name);
    void addProperties(const vCardPropertyList& properties);
    void clear() { m_properties.clear(); }
    const vCardProperty properties(const QString& name) const;
    const vCardPropertyList &properties() const { return m_properties; }
    vCardProperty property(const QString& name, const vCardParamList& params = vCardParamList(), bool strict = false) const;
    bool contains(const QString& property, const vCardParamList& params = vCardParamList(), bool strict = false) const;
    bool contains(const vCardProperty& property) const;
    bool isValid() const;

    int count() const;
    QByteArray toByteArray(vCardVersion version = VC_VER_2_1) const;

    bool saveToFile(const QString& filename) const;
    static bool saveToFile(QList<vCard>& cardList, const QString& filename);

    static QList<vCard> fromByteArray(const QByteArray& data);
    static QList<vCard> fromFile(const QString& filename);

    vCard &operator=(const vCard& other) { m_properties = other.m_properties; return *this; }
};

typedef QList<vCard> vCardList;

#endif // VCARD_H
