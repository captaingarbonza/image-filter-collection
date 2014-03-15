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

    connect( mFilterProcessor, SIGNAL( FilterDone(QImage) ), this, SLOT( UpdateCurrentImage(QImage) ) );

    InitImagePane();
	InitMenuBar();

	setCentralWidget( mScrollArea );
	setMinimumSize( mScrollArea->minimumSize() );
}

MainWindow::~MainWindow()
///
/// Destructor
///
{
	delete mOpenAction;
	delete mSaveAction;
	delete mFileMenu;

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
        QImage* image = new QImage;
        image->load( file_name );

        // Update the current image to this image
        UpdateCurrentImage( *image );

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
}

void
MainWindow::FilterTriggered( QAction* action )
{
	mFilterProcessor->StartFilter( action->objectName().toStdString(), *mCurrentImage );
}

void
MainWindow::ApplyCurrentFilter()
///
/// Sets up parameter values and triggers processing via the filter processing thread.
///
/// @return
///  Nothing
///
{
	//mFilterProcessingThread->BeginProcessing( new LayeredStrokesFilter() );
}

void
MainWindow::UpdateCurrentImage( QImage image )
///
/// Sets the pixmap displayed by the main window to a new image
///
/// @param image
///  QImage that will be converted giving us the new pixmap
///
/// @return
///  Nothing
{
	mCurrentImage = new QImage();
	*mCurrentImage = image.copy();
	mImageContainer->setPixmap( QPixmap::fromImage( image ) );
    mImageContainer->adjustSize();
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
MainWindow::InitMenuBar()
///
/// Initializes the menu bar and it's actions
///
/// @return
///  Nothing
///
{
	mOpenAction = new QAction( tr("&Open"), this );
	mSaveAction = new QAction( tr("&Save"), this );	

	///
	/// Ghost the save action as it needs an image to be loaded to function correctly.
	/// Connect the action so it turns back on when an image is set successfully.
	///
	mSaveAction->setDisabled( true );
	//connect( mFilterProcessingThread, SIGNAL( ImageLoaded(bool) ), mSaveAction, SLOT( setEnabled(bool) ) );

	///
	/// Connect the actions to their slots in mMainImagePane
	///
	connect( mOpenAction, SIGNAL( triggered() ), this, SLOT( Open() ) );
	connect( mSaveAction, SIGNAL( triggered() ), this, SLOT( Save() ) );

	///
	/// Add the actions to the menu
	///
	mFileMenu = menuBar()->addMenu( tr("&File") );
	mFileMenu->addAction( mOpenAction );
	mFileMenu->addAction( mSaveAction );

	mInvertAction = new QAction( tr("&Invert"), this);
	mInvertAction->setObjectName("invert");

	mFilterMenu = menuBar()->addMenu( tr("&Filters") );
	mFilterMenu->addAction( mInvertAction );

	connect( mFilterMenu, SIGNAL( triggered(QAction*) ), this, SLOT( FilterTriggered(QAction*) ) );
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
