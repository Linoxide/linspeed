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

