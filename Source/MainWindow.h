#ifndef _MAIN_WINDOW_
#define _MAIN_WINDOW_

#include <QApplication>
#include <QtWidgets>

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

	private:
        void InitImagePane();
		void InitMenuBar();

		QScrollArea* mScrollArea;
		QLabel* mImageContainer;

		QMenu* mFileMenu;

		QAction* mOpenAction;
		QAction* mSaveAction;
};

#endif