/*
  This file is part of Flow.

  Copyright (C) 2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TAGSTORAGEQSETTINGS_H
#define TAGSTORAGEQSETTINGS_H

#include "tagstorage.h"

class QSettings;

class TagStorageQSettings : public TagStorage
{
public:
    explicit TagStorageQSettings(QObject *parent = 0);

protected:
    void loadTags_impl() Q_DECL_OVERRIDE;
    void saveTags_impl() Q_DECL_OVERRIDE;
private:
    QSettings *m_settings;
};

#endif