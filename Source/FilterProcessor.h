#ifndef _FILTER_PROCESSOR_H_
#define _FILTER_PROCESSOR_H_

#include <QApplication>
#include <QtWidgets>
#include <string>
#include <map>

#include "Filter.h"

class FilterProcessor : public QThread
{
	Q_OBJECT

	public:
		FilterProcessor();
		~FilterProcessor();

		void StartFilter( std::string filter_name, QImage image );

	signals:
		void FilterDone( QImage result );

	private:
		void InitFilterLibrary();

		std::map<std::string, Filter*>  mFilterLibrary;

};

#endif