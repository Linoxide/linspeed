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

#include "speedmeter.h"

SpeedMeter::SpeedMeter(double _num, const QString &_format, QWidget *parent) 
	: QLabel(parent), format(_format) 
{
	setValue(_num);
	setAlignment(Qt::AlignCenter);
}

void SpeedMeter::setEmpty()
{
	setValue(0);
}

void SpeedMeter::setValue(double _num)
{
	num = _num;
	QString formattedNum = QString::number(num);
	if(num==0)
		formattedNum = QString::fromUtf8("—");
	setText(QString(format).arg(formattedNum));
}

void SpeedMeter::setFormat(const QString& _format)
{
	format = _format;
	setValue(num);
}
