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

#include <QDateTime>
#include <QPair>
#include <QSettings>
#include <QString>

class Results : public QObject {
	Q_OBJECT

private:
	QSettings settings;
	QList<QVariant> getList() const;

public:
	void addResult(double download, double upload, 
		const QDateTime &time=QDateTime::currentDateTime());
	QPair<double, double> getLastSpeed() const;
	bool empty() const;
	QString toString() const;

};

struct ResultsRecord {
	QDateTime time;
	double download;
	double upload;

	QString toString() const;
};

Q_DECLARE_METATYPE(ResultsRecord)

QDataStream &operator<<(QDataStream &out, const ResultsRecord &record);
QDataStream &operator>>(QDataStream &in, ResultsRecord &record);
