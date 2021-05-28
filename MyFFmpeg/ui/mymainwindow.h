/*

* Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.

*

* Author:     wangcong <wangcong@uniontech.com>

*

* Maintainer: wangcong <wangcong@uniontech.com>

*

* This program is free software: you can redistribute it and/or modify

* it under the terms of the GNU General Public License as published by

* the Free Software Foundation, either version 3 of the License, or

* any later version.

*

* This program is distributed in the hope that it will be useful,

* but WITHOUT ANY WARRANTY; without even the implied warranty of

* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the

* GNU General Public License for more details.

*

* You should have received a copy of the GNU General Public License

* along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H
//本项目的文件
#include "ui/myplaylistwidget.h"
#include "ui/myplaywidget.h"

//dtk的类
#include <DSlider>
#include <DMainWindow>
#include <DWidget>
#include <DLabel>
#include <DLineEdit>
#include <DToolButton>
#include <DToolBar>
#include <DMenu>
#include <DMenuBar>
#include <DTitlebar>

//qt的类
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QActionGroup>

//其他库

//cpp标准库

//linux系统库


DWIDGET_USE_NAMESPACE

/**
 * @brief 此类是主窗口类
 */
class MyMainWindow : public DMainWindow
{
public:
    MyMainWindow();

private:
    /**
     * @brief init 初始化主窗口界面
     */
    void initUI();

    /**
     * @brief 初始化工具栏
     */
    void initToolBar();

    /**
     * @brief 初始化播放窗口
     */
    void initPlayWidget();

    /**
     * @brief 初始化播放列表
     */
    void initPlayListWidget();

    /**
     * @brief 调用播放引擎播放视频
     */
    void playAV();

private :
    DToolBar* m_ToolBar;
    DWidget *m_mainWidget;

    MyPlayWidget *m_PlayWidget;
    MyPlayListWidget *m_PlayListWidget;

    MyPlayEngine *m_playEngine;

    QString currentFile;

};

#endif // MYMAINWINDOW_H
