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
	void addResult(double upload, double download, 
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

