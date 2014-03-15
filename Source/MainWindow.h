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
    	void LoadNewImage( QImage image );
    	void FilterTriggered( QAction* action );
    	void FilterComplete( QImage result );
    	void Undo();
    	void Redo();

    signals:
    	void UndoIsActive(bool active);
    	void RedoIsActive(bool active);

	private:
		void UpdateVisibleImage( QImage image );
		void UpdateEditMenuStates();

        void InitImagePane();
		void InitMenuBar();

		FilterProcessor* mFilterProcessor;

		QImage* mCurrentImage;
		QImage* mPreviousImage;
		QImage* mNextImage;

		QScrollArea* mScrollArea;
		QLabel* mImageContainer;

		QMenu* mFileMenu;
		QMenu* mEditMenu;
		QMenu* mFilterMenu;

		QAction* mOpenAction;
		QAction* mSaveAction;

		QAction* mUndoAction;
		QAction* mRedoAction;

		QAction* mInvertAction;
};

#endif