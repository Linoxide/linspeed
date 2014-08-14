/*
 *  Copyright (C) 2014 Linoxide <linoxide@gmail.com>
 *  Copyright (C) 2014 Michał Łuszczyk <michal.luszczyk@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef THEME_H
#define THEME_H

#include <QList>
#include <QString>

struct Theme {
	Theme(const QString& _name, int _size, const QString &_filenamePrefix);
	Theme(const Theme& theme);

	enum Size {
		Large,
		Small
	};

	QString name;
	int size;
	QString filenamePrefix;

	static QList<Theme> listThemes();
};

#endif

