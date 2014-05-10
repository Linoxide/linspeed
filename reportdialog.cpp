#include <QDialogButtonBox>
#include <QVBoxLayout>
#include "reportdialog.h"
#include "results.h"

ReportDialog::ReportDialog(QWidget *parent) : QDialog(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);

	Results res;

	text = new QTextEdit;
	text->setReadOnly(true);
	text->setPlainText(res.toString());

	QDialogButtonBox *box = new QDialogButtonBox;
	box->addButton(QDialogButtonBox::Close);
	connect(box, SIGNAL(rejected()), this, SLOT(close()));

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(text);
	layout->addWidget(box);
}
