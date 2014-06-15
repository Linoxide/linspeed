#include <QDialogButtonBox>
#include <QLabel>
#include <QVBoxLayout>
#include "aboutdialog.h"

const char ABOUT_TEXT[] = 
"Linspeed by LinOxide<br>"
"See <a href=\"http://linoxide.com/products/linspeed.html\">"
"http://linoxide.com/products/linspeed.html</a> for details.<br>"
"<br>"
"Developed by &lt;insert dev's name&gt;.<br>"
"Graphics by &lt;insert designer's name&gt;.<br>"
"<br>"
"This application is based on <a href=\"speedof.me\">SpeedOf.Me API</a>.";

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