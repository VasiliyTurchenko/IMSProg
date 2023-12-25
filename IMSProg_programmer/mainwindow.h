/*
 * Copyright (C) 2023 Mikhail Medvedev <e-ink-reader@yandex.ru>
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <unistd.h>
#include "qhexedit.h"
#include "dialogsp.h"
#include "dialogabout.h"
#include "dialoginfo.h"
#include "dialogsfdp.h"
#include "searchdialog.h"
extern "C" {
#include "bitbang_microwire.h"
#include "ch341a_gpio.h"
#include "ch341a_i2c.h"
#include "ch341a_spi.h"
#include "flashcmd_api.h"
#include "i2c_eeprom_api.h"
#include "mw_eeprom_api.h"
#include "nandcmd_api.h"
#include "res.h"
#include "snorcmd_api.h"
#include "spi_controller.h"
#include "spi_eeprom.h"
#include "spi_eeprom_api.h"
#include "spi_nand_flash.h"
#include "timer.h"
#include "types.h"
}


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void receiveAddr(QString);
    void receiveAddr2(QString);

private slots:
    void progInit();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_comboBox_size_currentIndexChanged(int index);
    void on_comboBox_page_currentIndexChanged(int index);
    void on_actionDetect_triggered();
    void on_actionSave_triggered();
    void on_actionErase_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionOpen_triggered();
    void on_actionWrite_triggered();
    void on_actionRead_triggered();
    void on_actionExit_triggered();
    void on_comboBox_man_currentIndexChanged(int index);
    void on_comboBox_name_currentIndexChanged(const QString &arg1);
    void on_actionVerify_triggered();
    void on_pushButton_3_clicked();
    void on_actionSave_Part_triggered();
    void on_actionLoad_Part_triggered();
    void on_actionFind_Replace_triggered();
    void on_comboBox_type_currentIndexChanged(int index);
    void on_actionAbout_triggered();
    void on_actionChecksum_calculate_triggered();
    void on_actionEdit_chips_Database_triggered();
    void doNotDisturb();
    void doNotDisturbCancel();
    void on_actionStop_triggered();
    void on_pushButton_4_clicked();
    void on_actionChip_info_triggered();

private:
    enum class chipType : uint8_t {chipTypeSPI = 0U,
                                   chipType24EE,
                                   chipType93EE,
                                   chipType25EE,
                                   chipType95EE};

    Ui::MainWindow *ui;
    QColor defaultTextColor;
    QString grnKeyStyle, redKeyStyle;
    QString lastDirectory;
    int statusCH341;
    QByteArray chipData;
    uint32_t currentChipSize, currentNumBlocks, currentBlockSize, currentPageSize;
    uint8_t currentAlgorithm;
    chipType currentChipType;
    unsigned int currentAddr4bit;
    bool isHalted;
    QString bytePrint(unsigned char z);

    struct chip_data {
        QString chipManuf;
        QString chipTypeTxt;
        QString chipName;
        uint8_t chipJedecIDMan;
        uint8_t chipJedecIDDev;
        uint8_t chipJedecIDCap;
        uint32_t chipSize;
        uint16_t sectorSize;
        uint8_t chipTypeHex;
        uint8_t algorithmCode;
        int delay;
        uint8_t addr4bit;
        uint32_t blockSize;
        uint8_t eepromPages;
        QString chipVCC;
    };
    chip_data chips[2000];
    int max_rec;
    QString fileName;
    QHexEdit *hexEdit;
    QString sizeConvert(int a);
    QString hexiAddr(uint32_t a);
    uint32_t hexToInt(QString str);
    QString getCRC32();
    void ch341StatusFlashing();
    QByteArray block;
    uint32_t blockStartAddr, blockLen;
};

#endif // MAINWINDOW_H
