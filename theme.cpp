#include "theme.h"

Theme::Theme(const QString& _name, int _size, const QString &_filenamePrefix)
	: name(_name), size(_size), filenamePrefix(_filenamePrefix) {}

Theme::Theme(const Theme& theme) 
	: name(theme.name), size(theme.size), filenamePrefix(theme.filenamePrefix) {}

QList<Theme> Theme::listThemes()
{
	QList<Theme> list;
	list.append(Theme("Native Large", Large, "nativelarge"));
	list.append(Theme("Native Small", Small, "nativesmall"));
	list.append(Theme("Striped Large", Large, "stripedlarge"));
	list.append(Theme("Bordeaux Large", Large, "bordeauxlarge"));

	return list;
}
