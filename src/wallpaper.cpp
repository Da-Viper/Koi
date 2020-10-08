#include "wallpaper.h"

Wallpaper::Wallpaper()
{

}

void Wallpaper::setWallpaper(const QVariant& wallFile)
{
    bus = new QDBusConnection(QDBusConnection::sessionBus());
    QDBusInterface interface("org.kde.plasmashell", "/PlasmaShell", "org.kde.PlasmaShell", *bus);
    QString script;
    script = "var Desktops = desktops();";
    script += "for (i=0;i<Desktops.length;i++) {";
    script += "d = Desktops[i];";

    auto no = wallFile.toInt();
    if (no == 0) {
        script += "d.wallpaperPlugin = \"org.kde.image\";";
        script += "d.currentConfigGroup = Array(\"Wallpaper\", \"org.kde.image\", \"General\");";
        script += "d.writeConfig(\"Image\", \"file://";
    }
    else {
        script += "d.wallpaperPlugin = \"org.kde.potd\";";
        script += "d.currentConfigGroup = Array(\"Wallpaper\",\"org.kde.potd\", \"General\");";
        script += "d.writeConfig(\"Provider\", \"unsplash\");";
        script += "d.writeConfig(\"Category\", \"";
    }
    script += wallFile.toString();
    script += "\");}";
    interface.call("evaluateScript", script);
}
Wallpaper::~Wallpaper()
{
    delete bus;
}
