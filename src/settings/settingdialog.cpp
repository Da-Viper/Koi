/*
 * this is the dialog widget for all settings in  koi
 * inherited from kPagedialog and has three widget item
 * -General , -Profile , and Others
 * */
#include "settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent)
	:
	KPageDialog(parent),
	_generalUi(nullptr),
	_profileUi(nullptr)
{
	// KOI Settings Location on the drive
	settings = new QSettings(QDir::homePath() + "/.config/koirc", QSettings::NativeFormat);

	setWindowTitle("Settings Page");
	setFaceType(KPageDialog::Tabbed);

	//Adding Pages
	// General page
	const QString generalPageName = ("General");
	_generalUi = new GeneralSettings(this, settings);
	KPageWidgetItem *generalPageItem = this->addPage(_generalUi, generalPageName);
	generalPageItem->setHeader(generalPageName);
	generalPageItem->setIcon(QIcon::fromTheme(QStringLiteral("firewall")));

	// Profiles Page
	const QString profilePageName = ("Profiles");
	_profileUi = new ProfileSettingsDialog(this, settings);
	KPageWidgetItem *profilePageItem = addPage(_profileUi, profilePageName);
	profilePageItem->setHeader(profilePageName);
	profilePageItem->setIcon(QIcon::fromTheme("style"));

	//others Page

	connect(this, &SettingDialog::accepted, this, &SettingDialog::slotOkClicked);
}

SettingDialog::~SettingDialog()
{
	delete _generalUi;
	delete _profileUi;
	delete settings;
}
void SettingDialog::slotOkClicked()
{
	_generalUi->applySetting();
}

