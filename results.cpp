#include <QList>
#include "results.h"

const int RESULTS_MAX_SIZE = 5;

QList<QVariant> Results::getList() const
{
	QVariant listVar = settings.value("results/data", QList<QVariant>());
	return listVar.toList();
}

void Results::addResult(double download, double upload, const QDateTime& time)
{
	ResultsRecord rec = {time, download, upload};
	QVariant var = QVariant::fromValue(rec);

	QList<QVariant> list = getList();

	while(list.size()>=RESULTS_MAX_SIZE) {
		list.removeAt(RESULTS_MAX_SIZE-1);
	}

	list.insert(0, var);

	settings.setValue("results/data", list);
}

QPair<double, double> Results::getLastSpeed() const
{
	if(empty())
		return qMakePair(0., 0.);

	QVariant first = getList()[0];
	ResultsRecord rec = first.value<ResultsRecord>();
	return qMakePair(rec.download, rec.upload);
}

bool Results::empty() const
{
	return getList().empty();
}

QString Results::toString() const
{
	QString str;
	QList<QVariant> list = getList();
	for(int i=0; i<list.size(); ++i) {
		ResultsRecord rec = list[i].value<ResultsRecord>();
		str += rec.toString() + '\n';
	}

	return str;
}

QString ResultsRecord::toString() const
{
	QString str = "%1 %2 Mbps %3 Mbps";
	str = str.arg(time.toString("yyyy-MM-dd hh-mm ap"));
	str = str.arg(download).arg(upload);
	return str;
}

QDataStream &operator<<(QDataStream &out, const ResultsRecord &record)
{
	out << record.time << record.download << record.upload;
	return out;
}

QDataStream &operator>>(QDataStream &in, ResultsRecord &record)
{
	in >> record.time >> record.download >> record.upload;
	return in;
}

