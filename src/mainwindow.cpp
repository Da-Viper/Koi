#include "mainwindow.h"
#include "ui_mainwindow.h"

Bosma::Scheduler s(2);

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow)
{

	trayIcon = new QSystemTrayIcon(this);
	this->trayIcon->setIcon(QIcon(":/resources/icons/koi_tray.png")); // Set tray icon - Not sure why svg doesn't work
	this->trayIcon->setVisible(true);
	trayMenu = this->createMenu();
    this->trayIcon->setContextMenu(trayMenu);   // Set tray context menu

    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated); // System tray interaction
    ui->setupUi(this);

    // TODO use an enum for this maybe ?
    if (m_settings.value("schedule").toString() == "custom time") {
        runSchedule();
    }

    ui->resMsg->hide();
    auto actionRes = new QAction("Restart", this);
    actionRes->setIcon(QIcon::fromTheme("view-refresh"));
    connect(actionRes, &QAction::triggered, this, &MainWindow::on_actionRestart_triggered);
    ui->resMsg->addAction(actionRes);
}

MainWindow::~MainWindow()
{
	this->setVisible(false);
	delete ui;
}


// Override window managing events
void MainWindow::closeEvent(QCloseEvent *event)
{ // Override close event
	event->ignore();
	toggleVisibility();
}

void MainWindow::runSchedule()
{
    QString currentName(Utils::startupTimeCheck()); // get the profile to be used.
    if (!currentName.isEmpty() || !currentName.isNull()) {
        auto currentProfile = ProfileManager::instance()->getProfile(currentName);
        Utils current(currentProfile);
        current.go();
    }

    auto manager = ProfileManager::instance();
    //Schedule other Profiles.
    m_settings.beginGroup("Favourites");
    auto profileSchedList = manager->allProfiles();


    for (const auto profile : profileSchedList) {
        if (manager->isFavourite(profile->name())) {
            auto utils = QExplicitlySharedDataPointer<Utils>(new Utils(profile));
            auto favTime = QTime::fromString(m_settings.value(profile->name()).toString());
            if (!favTime.isNull()) {
                //TODO reimplement schedule
                schedule(utils, favTime);
            }
        }
    }
    m_settings.endGroup();
}
// SysTray related functionality
QMenu *MainWindow::createMenu() // Define context menu items for SysTray - R-click to show context menu
{
	// Tray action menu
	auto actionMenuQuit = new QAction("&Quit", this); // Quit app
	connect(actionMenuQuit, &QAction::triggered, this, &QCoreApplication::quit);
	auto actionMenuLight = new QAction("&Light", this);                                    // Switch to light
	connect(actionMenuLight, &QAction::triggered, this, &MainWindow::on_lightBtn_clicked); //Doesn't work.
	auto actionMenuDark = new QAction("&Dark", this);                                      //Switch to dark
	connect(actionMenuDark, &QAction::triggered, this, &MainWindow::on_darkBtn_clicked);   //Doesn't work.
	auto actionMenuToggle = new QAction("&Toggle Window", this);
	connect(actionMenuToggle, &QAction::triggered, this, &MainWindow::toggleVisibility);

	// Build tray items
	auto trayMenu1 = new QMenu(this);
	trayMenu1->addAction(actionMenuToggle);
	trayMenu1->addAction(actionMenuLight);
	trayMenu1->addAction(actionMenuDark);
	trayMenu1->addAction(actionMenuQuit);
	return trayMenu1;
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason) // Define actions for SysTray L&M-click
{
	switch (reason) {
	case QSystemTrayIcon::Trigger: // Left-click to toggle window visibility
		toggleVisibility();
		break;

		//        case QSystemTrayIcon::MiddleClick: // Middle-click to toggle between light and dark
		//            utils.notify("Hello!", "You middle-clicked me", 0); // Must implement toggle
		//            break;

		// Must understand tray better - Why can't right click be part of switch statement?

	default: // Need to understand switch statements better - Why is this required?
		break;
	}
}

// Independent functions
void MainWindow::toggleVisibility()
{
	if (this->isVisible() == 0) {
		this->setVisible(true);
		this->activateWindow();
	}
	else {
		this->setVisible(false);
	}
}

void MainWindow::schedule(QExplicitlySharedDataPointer<Utils>(utils), QTime time)
{
	auto favTime = time;

	int cronMin = (favTime.minute() < 0) ? 0 : favTime.minute();
	int cronHr = (favTime.hour() < 0) ? 0 : favTime.hour();

	std::string cronJ = std::to_string(cronMin) + " " + std::to_string(cronHr) + " * * *";

	s.cron(cronJ, [utils]()
	{
		utils->go();
	});
}

// Functionality of buttons - Related to program navigation, interaction and saving settings
void MainWindow::on_prefsBtn_clicked() // Preferences button - Sets all preferences as found in koi.conf// file
{
	auto *dialog = new SettingDialog(this);
	dialog->setModal(true);
	dialog->show();
}

void MainWindow::on_lightBtn_clicked()
{
	QString currentName("light"); // get the profile to be used.
	auto currentProfile = ProfileManager::instance()->getProfile(currentName);
	Utils current(currentProfile);
	current.go();
}

void MainWindow::on_darkBtn_clicked()
{
	QString currentName("dark"); // get the profile to be used.
	auto currentProfile = ProfileManager::instance()->getProfile(currentName);
	Utils current(currentProfile);
	current.go();
}

//void MainWindow::on_hiddenCheckBox_stateChanged(int hiddenEnabled)
//{
//    m_settings.setValue("start-hidden", hiddenEnabled);
//	ui->resMsg->setText(tr("To set Hidden , Koi must be restarted."));
//	ui->resMsg->setMessageType(KMessageWidget::Warning);
//	ui->resMsg->animatedShow();
//	QTest::qWait(3000);
//	ui->resMsg->animatedHide();
//}


// Menubar actions
void MainWindow::on_actionQuit_triggered() // Quit app
{
	QApplication::quit();
}

void MainWindow::on_actionPrefs_triggered() // Set preferences
{
	on_prefsBtn_clicked(); // Triggers "Preferences" button
}

void MainWindow::on_actionAbout_triggered() // Open about dialog
{
	auto *about = new About(this);
	about->open();
}

void MainWindow::on_actionHide_triggered() // Hide to tray
{
	this->setVisible(false);
}
void MainWindow::on_actionRestart_triggered()
{
	QProcess::startDetached(QApplication::applicationFilePath(), QStringList());
	exit(12);
}

