#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QMessageBox>
#include "VirtualNES.h"
#include "nes/NesRom.hpp"

VirtualNES::VirtualNES(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.actionWebsite, &QAction::triggered, [] {
        QDesktopServices::openUrl(QUrl{ "https://ohto-ai-dev.github.io/vNes/" });
        });

    connect(ui.actionLoadNesRom, &QAction::triggered, [this] {
        QString path = QFileDialog::getOpenFileName(this, "Open NES Rom", "", "NES Rom (*.nes)");
        NesRom rom;
        try {
            rom.load(path.toStdString());
        }
        catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", e.what());
            return;
        }
        const auto& prg_rom = rom.prg_rom();
        const auto& chr_rom = rom.chr_rom();
        QMessageBox::information(this, "Tip", QString::asprintf("PRG ROM size: %d bytes, CHR ROM size: %d bytes", prg_rom.size(), chr_rom.size()));
        });
}

VirtualNES::~VirtualNES()
{}
