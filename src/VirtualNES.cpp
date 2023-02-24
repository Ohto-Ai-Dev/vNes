#include "VirtualNES.h"
#include <QDesktopServices>
#include <QUrl>

VirtualNES::VirtualNES(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.actionWebsite, &QAction::triggered, [] {
        QDesktopServices::openUrl(QUrl{ "https://ohto-ai-dev.github.io/vNes/" });
        });

}

VirtualNES::~VirtualNES()
{}
