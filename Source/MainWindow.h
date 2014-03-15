#ifndef _MAIN_WINDOW_
#define _MAIN_WINDOW_

#include <QApplication>
#include <QtWidgets>

#include "FilterProcessor.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		MainWindow();
		~MainWindow();

		void Resize();
		void Center();

	public slots:
    	void Open();
    	void Save();
    	void ApplyCurrentFilter();
    	void UpdateCurrentImage( QImage image );
    	void FilterTriggered( QAction* action );
	private:
        void InitImagePane();
		void InitMenuBar();

		FilterProcessor* mFilterProcessor;

		QImage* mCurrentImage;
		QImage* mPreviousImage;
		QImage* mNextImage;

		QScrollArea* mScrollArea;
		QLabel* mImageContainer;

		QMenu* mFileMenu;
		QMenu* mFilterMenu;

		QAction* mOpenAction;
		QAction* mSaveAction;

		QAction* mInvertAction;
};

#endif