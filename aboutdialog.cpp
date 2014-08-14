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

#include <QDialogButtonBox>
#include <QLabel>
#include <QVBoxLayout>
#include "aboutdialog.h"

const char ABOUT_TEXT[] = 
"Linspeed by LinOxide<br>"
"Version 1.0<br>"
"<br>"
"See <a href=\"http://linoxide.com/linspeed/\">"
"http://linoxide.com/linspeed/</a> for details.<br>"
"This application is based on <a href=\"http://speedof.me\">SpeedOf.Me API</a>.";

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent)
{
	QLabel *label = new QLabel;
	label->setOpenExternalLinks(true);
	label->setText(ABOUT_TEXT);
	label->setTextFormat(Qt::RichText);

	QDialogButtonBox *box = new QDialogButtonBox;
	box->addButton(QDialogButtonBox::Close);
	connect(box, SIGNAL(rejected()), this, SLOT(close()));

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(label);
	layout->addWidget(box);

}
