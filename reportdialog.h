#include <QDialog>
#include <QTextEdit>

class ReportDialog : public QDialog {
	Q_OBJECT

public:
	ReportDialog(QWidget *parent = 0);

private:
	QTextEdit *text;

private slots:

};
