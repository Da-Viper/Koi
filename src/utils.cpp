#include "headers/utils.h"

Utils::Utils()
{

}

// Light/Dark management


// Get stuff
QStringList Utils::getPlasmaStyles(void) // Get all available plasma styles
{
    QDir stylesLocalDir(QDir::homePath() + "/.local/share/plasma/look-and-feel");
    QDir stylesSystemDir("/usr/share/plasma/look-and-feel");
    QStringList plasmaStyles = stylesLocalDir.entryList(QDir::Dirs) + stylesSystemDir.entryList(QDir::Dirs);
    plasmaStyles.removeDuplicates();
    plasmaStyles.removeFirst();
    plasmaStyles.removeFirst();
    return plasmaStyles;
}
QStringList Utils::getColorSchemes(void) // Get all available color schemes
{
    QDir colorsLocalDir(QDir::homePath() + "/.local/share/color-schemes");
    QDir colorsSystemDir("/usr/share/color-schemes");
    colorsLocalDir.setNameFilters(QStringList()<<"*.colors");
    colorsSystemDir.setNameFilters(QStringList()<<"*.colors");
    QStringList colorSchemes = colorsLocalDir.entryList() + colorsSystemDir.entryList();
    colorSchemes.removeDuplicates();
    colorSchemes.removeFirst();
    colorSchemes.removeFirst();
    return colorSchemes;
}
QStringList Utils::getIconThemes(void) // Get all available icont themes
{
    QDir iconsOldLocalDir(QDir::homePath() + "/.icons");
    QDir iconsLocalDir(QDir::homePath() + "/.local/share/icons");
    QDir iconsSystemDir("/usr/share/icons");
    QStringList iconThemes = iconsOldLocalDir.entryList(QDir::Dirs) + iconsLocalDir.entryList(QDir::Dirs) + iconsSystemDir.entryList(QDir::Dirs);
    iconThemes.removeDuplicates();
    iconThemes.removeFirst();
    iconThemes.removeFirst();
    return iconThemes;
}
QStringList Utils::getGtkThemes(void) // Get all available gtk themes
{
    QDir gtkLocalDir(QDir::homePath() + "/.themes");
    QDir gtkSystemDir("/usr/share/themes");
    QStringList gtkThemes = gtkLocalDir.entryList(QDir::Dirs) + gtkSystemDir.entryList(QDir::Dirs);
    gtkThemes.removeDuplicates();
    gtkThemes.removeFirst();
    gtkThemes.removeFirst();
    return gtkThemes;
}

// Manage switching themes functions
void Utils::timeLoopLight()
{

}

// Manage koi start on system startup
void Utils::startupCreate() // Create .desktop file in ~/.config/startup
{
    // Do stuff
}
void Utils::startupDelete() // Remove .desktop file from ~/.config/startup
{
    // Do stuff
}
