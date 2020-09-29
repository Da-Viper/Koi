#include "gtk.h"

Gtk::Gtk()
{

}

void Gtk::setGtk(const QString& gtkTheme)
{
    QDBusInterface interface("org.kde.GtkConfig", "/GtkConfig", "org.kde.GtkConfig");
    interface.call("setGtk2Theme", gtkTheme);
    interface.call("setGtk3Theme", gtkTheme);
}

QStringList Gtk::getGtkThemes() // Get all available gtk themes
{
    QDir gtkLocalDir(QDir::homePath() + "/.themes");
    QDir gtkSystemDir("/usr/share/themes");
    QStringList gtkThemes = gtkLocalDir.entryList(QDir::Dirs) + gtkSystemDir.entryList(QDir::Dirs);
    gtkThemes.removeDuplicates();
    gtkThemes.removeFirst();
    gtkThemes.removeFirst();
    return gtkThemes;
}
