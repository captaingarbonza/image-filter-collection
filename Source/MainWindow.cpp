#include "MainWindow.h"

MainWindow::MainWindow()
///
/// Constructor
///
: mCurrentImage( NULL ),
  mPreviousImage( NULL ),
  mNextImage( NULL )
{
    setWindowTitle( tr( "Image Filter Collection" ) );
    
	setMaximumSize( QSize( 1250, 650 ) );
    setMinimumSize( QSize( 200, 200 ) );

    mFilterProcessor = new FilterProcessor();

    connect( mFilterProcessor, SIGNAL( FilterDone(QImage) ), this, SLOT( LoadNewImage(QImage) ) );

    InitImagePane();
    
	InitFileMenu();
	InitEditMenu();
	InitFilterMenu();

	setCentralWidget( mScrollArea );
	setMinimumSize( mScrollArea->minimumSize() );

	mStatusText = new QLabel;
	statusBar()->addWidget(mStatusText);
	connect( mFilterProcessor, SIGNAL( FilterStatus(QString) ), this, SLOT( StatusBarUpdated(QString) ) );
}

MainWindow::~MainWindow()
///
/// Destructor
///
{
	delete mOpenAction;
	delete mSaveAction;
	delete mFileMenu;

	delete mUndoAction;
	delete mRedoAction;
	delete mEditMenu;

	delete mBoxBlurAction;
	delete mGaussianAction;
	delete mInvertAction;
	delete mFilterMenu;

	delete mFilterProcessor;

	delete mPreviousImage;
	delete mCurrentImage;
	delete mNextImage;
}

void
MainWindow::Open()
///
/// Displays an open file dialog and sets the current image to be the one selected by the user.
///
/// @return
///  Nothing
///
{
	const QString default_dir_key("default_dir");
	QSettings app_settings;

	// Display an open file dialog at the default folder in the application setting
	QString file_name = QFileDialog::getOpenFileName( this, tr("Open File"), app_settings.value(default_dir_key).toString(), "Images (*.png *.bmp *.jpg)" );
    if( file_name != "" )
    {
    	// Save the chosen folder as the default in the application settings
    	QDir current_dir;
        app_settings.setValue(default_dir_key, current_dir.absoluteFilePath(file_name));

        // Load the chosen file as the unprocessed image
        QImage image;
        image.load( file_name );

        // Update the current image to this image
        LoadNewImage( image );

        // Resize window to fit new image
        Resize();
    }
}

void
MainWindow::Save()
///
/// Displays a save file dialog and saves the current image to a file specified by the user.
///
/// @return
///  Nothing
///
{
	QString file_name = QFileDialog::getSaveFileName( this, tr("Save File"), "", "Image (*.png *.bmp *.jpg" );
    if( file_name != "" && mCurrentImage != NULL && !mCurrentImage->isNull() )
    {
        mCurrentImage->save( file_name );
    }
}

void
MainWindow::FilterTriggered( QAction* action )
///
/// Triggers a filter on the current image by calling the filter processor.
///
/// @param action
///  The action that was triggered. The action's object name property is the name of the
///  filter to be triggered.
///
/// @return
///  Nothing. The filter processor is in charge of letting us know when the filtering is done.
///
{
	if( mCurrentImage != NULL && !mCurrentImage->isNull() && action != NULL )
	{
		StatusBarUpdated( QString("Processing...") );
		mFilterProcessor->StartFilter( action->objectName().toStdString(), *mCurrentImage );
	}
	else
	{
		StatusBarUpdated( QString("Problem with image. Filter canceled.") );
	}
}

void 
MainWindow::Undo()
///
/// Returns to the previous image state
///
/// @return
/// Nothing
///
{
	// Move current image to the next image slot so we can return to it
	// with a redo
	if( mNextImage != NULL )
	{
		delete mNextImage;
	}
	mNextImage = mCurrentImage;

	// Set previous image as the current image
	mCurrentImage = mPreviousImage;
	mPreviousImage = NULL;

	// Update the state of the GUI
	UpdateVisibleImage( *mCurrentImage );
	UpdateEditMenuStates();
}

void 
MainWindow::Redo()
///
/// Returns to the image prior to an undo
///
/// @return
///  Nothing
///
{
	// Move the current image to the previous image slot
	if( mPreviousImage != NULL )
	{
		delete mPreviousImage;
	}
	mPreviousImage = mCurrentImage;

	// Set next image as the current image
	mCurrentImage = mNextImage;
	mNextImage = NULL;

	// Update the state of the GUI
	UpdateVisibleImage( *mCurrentImage );
	UpdateEditMenuStates();
}

void 
MainWindow::LoadNewImage( QImage image )
///
/// Loads a new image
///
/// @param image
///  The image to be loaded
///
/// @return
///  Nothing
///
{
	// Move the past image to be the previous image
	if( mPreviousImage != NULL )
	{
		delete mPreviousImage;
	}

	mPreviousImage = mCurrentImage;

	// Delete next image if it exists, redo functionality will be reset.
	if( mNextImage != NULL )
	{
		delete mNextImage;
		mNextImage = NULL;
	}

	// Set this image as the current image
	mCurrentImage = new QImage();
	*mCurrentImage = image.copy();

	// Update the state of the GUI
	emit ImageLoaded( mCurrentImage != NULL && !mCurrentImage->isNull() );

	UpdateVisibleImage( image );
	UpdateEditMenuStates();
}

void
MainWindow::UpdateVisibleImage( QImage image )
///
/// Sets the pixmap displayed by the main window to a new image
///
/// @param image
///  QImage that will be converted giving us the new pixmap
///
/// @return
///  Nothing
{
	mImageContainer->setPixmap( QPixmap::fromImage( image ) );
    mImageContainer->adjustSize();
}

void
MainWindow::UpdateEditMenuStates()
///
/// Emits signals to disable or enable undo and redo functionality
/// depending on whether or not an appropriate image exists to return to.
///
/// @return
///  Nothing
///
{
	emit UndoIsActive( mPreviousImage != NULL );
	emit RedoIsActive( mNextImage != NULL );
}

void
MainWindow::StatusBarUpdated( QString text )
{
	mStatusText->setText(text);
}

void
MainWindow::Resize()
///
/// Resizes the window to the size of the current image if it is within the window size limits.
/// Centers the window based on the new size.
///
/// @return
///  Nothing
///
{
	this->resize( mImageContainer->size() );
	Center();
}

void
MainWindow::Center()
///
/// Positions the window in the center of the screen.
///
/// @return
///  Nothing
///
{
  int x = (QApplication::desktop()->width() - this->width()) / 2;
  int y = (QApplication::desktop()->height()  - this->height()) / 2;
  this->move(x,y);
}

void
MainWindow::InitFileMenu()
///
/// Initializes the file menu and it's associated actions
///
/// @return
///  Nothing
///
{
	mOpenAction = new QAction( tr("&Open"), this );
	mSaveAction = new QAction( tr("&Save"), this );	

	// Ghost the save action as it needs an image to be loaded to function correctly.
	// Connect the action so it turns back on when an image is set successfully.
	mSaveAction->setDisabled( true );
	connect( this, SIGNAL( ImageLoaded(bool) ), mSaveAction, SLOT( setEnabled(bool) ) );

	// Connect the actions to their slots
	connect( mOpenAction, SIGNAL( triggered() ), this, SLOT( Open() ) );
	connect( mSaveAction, SIGNAL( triggered() ), this, SLOT( Save() ) );

	mFileMenu = menuBar()->addMenu( tr("&File") );
	mFileMenu->addAction( mOpenAction );
	mFileMenu->addAction( mSaveAction );
}

void
MainWindow::InitEditMenu()
///
/// Initializes the edit menu and it's associated actions
///
/// @return
///  Nothing
///
{
	mUndoAction = new QAction( tr("&Undo"), this);
	mRedoAction = new QAction( tr("&Redo"), this);

	mEditMenu = menuBar()->addMenu( tr("&Edit") );
	mEditMenu->addAction( mUndoAction );
	mEditMenu->addAction( mRedoAction );

	// Connect the menu actions to their respective slots
	connect( mUndoAction, SIGNAL( triggered() ), this, SLOT( Undo() ) );
	connect( mRedoAction, SIGNAL( triggered() ), this, SLOT( Redo() ) );

	// Disable the actions until the main window broadcasts for them to be active
	mUndoAction->setDisabled( true );
	mRedoAction->setDisabled( true );

	connect( this, SIGNAL( UndoIsActive(bool) ), mUndoAction, SLOT( setEnabled(bool) ) );
	connect( this, SIGNAL( RedoIsActive(bool) ), mRedoAction, SLOT( setEnabled(bool) ) );
}

void
MainWindow::InitFilterMenu()
///
/// Initializes the filter menu and it's associated actions
///
/// @return
///  Nothing
///
{
	// Create the filter menu actions and add their associated filter
	// name as the object name of the action so it can be retrieved later.
	mBoxBlurAction = new QAction( tr("&Box Blur"), this);
	mBoxBlurAction->setObjectName("box_blur");
	mGaussianAction = new QAction( tr("&Gaussian Blur"), this);
	mGaussianAction->setObjectName("gaussian");
	mInvertAction = new QAction( tr("&Invert"), this);
	mInvertAction->setObjectName("invert");

	mFilterMenu = menuBar()->addMenu( tr("&Filters") );
	mFilterMenu->addAction( mBoxBlurAction );
	mFilterMenu->addAction( mGaussianAction );
	mFilterMenu->addAction( mInvertAction );

	// Call the filter triggered slot when any menu item is triggered.
	connect( mFilterMenu, SIGNAL( triggered(QAction*) ), this, SLOT( FilterTriggered(QAction*) ) );

	// Disable the filter menu when no image is loaded
	mFilterMenu->setDisabled( true );
	connect( this, SIGNAL( ImageLoaded(bool) ), mFilterMenu, SLOT( setEnabled(bool) ) );
}

void
MainWindow::InitImagePane()
///
/// Initializes the central pane the contains the image to be filtered.
///
/// @return
///  Nothing
///
{
    mScrollArea = new QScrollArea;
    mScrollArea->setBackgroundRole( QPalette::Dark );
    
    mImageContainer = new QLabel;
    mImageContainer->setBackgroundRole( QPalette::Base );
    mImageContainer->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    mImageContainer->setScaledContents( true );
    
    mScrollArea->setWidget( mImageContainer );
   	mScrollArea->setMaximumSize( QSize( 1250, 650 ) );
    mScrollArea->setMinimumSize( QSize( 200, 200 ) );
}
