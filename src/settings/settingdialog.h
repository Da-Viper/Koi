#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

//QT
#include <QDialog>
#include <QModelIndexList>
#include <QListWidgetItem>
#include <QSettings>
#include <QDir>

//KDE
#include <KPageDialog>

//koi
#include "generalsettings.h"
#include "profilesettingsdialog.h"
#include "scheduleprofile.h"

namespace Ui
{
class GeneralSettings;
class ScheduleProfile;
}

class SettingDialog: public KPageDialog
{
Q_OBJECT

public:
	explicit SettingDialog(QWidget *parent = nullptr);
	~SettingDialog() override;

private slots:
	void slotOkClicked();

private:
//    QMap<KPageWidgetItem *, Page> _pages;

	GeneralSettings *_generalUi;
	ProfileSettingsDialog *_profileUi;
	ScheduleProfile *_scheduleUi;
	QSettings *settings;
};

#endif // SETTINGDIALOG_H
