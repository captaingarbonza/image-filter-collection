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
    	void Undo();
    	void Redo();

    signals:
    	void UndoIsActive(bool active);
    	void RedoIsActive(bool active);
    	void ImageLoaded(bool loaded);

	private:
		void UpdateVisibleImage( QImage image );
		void UpdateEditMenuStates();

        void InitImagePane();
		void InitFileMenu();
		void InitEditMenu();
		void InitFilterMenu();

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