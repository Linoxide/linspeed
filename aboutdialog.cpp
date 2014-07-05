#include <QDialogButtonBox>
#include <QLabel>
#include <QVBoxLayout>
#include "aboutdialog.h"

const char ABOUT_TEXT[] = 
"Linspeed by LinOxide<br>"
"See <a href=\"http://linoxide.com/tools/linspeed.html\">"
"http://linoxide.com/tools/linspeed.html</a> for details.<br>"
"Contact: <a href=\"mailto:linspeed@linoxide.com\">"
"linspeed@linoxide.com</a>.<br>"
"<br>"
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
