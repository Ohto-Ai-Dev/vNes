#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VirtualNES.h"

class VirtualNES : public QMainWindow
{
    Q_OBJECT

public:
    VirtualNES(QWidget* parent = nullptr);
    ~VirtualNES();

private:
    Ui::VirtualNESClass ui;
};


