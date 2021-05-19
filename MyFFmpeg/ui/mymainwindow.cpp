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
#include "mymainwindow.h"

namespace {
    //const int TOOLBAR_HEIGHT = 244;
    const int TOOLBAR_WIDTH = 40;
    //const int BUTTON_SPACING = 10;
    const QSize TOOL_ICON_SIZE = QSize(30, 30);
    const QSize TOOL_BUTTON_SIZE = QSize(38, 38);
    const QSize TOOL_SLIDERBlUR_SIZE = QSize(35, 190);
    const QSize TOOL_SLIDER_SIZE = QSize(40, 180);
    const QSize SPLITTER_SIZE = QSize(30, 1);
}

MyMainWindow::MyMainWindow()
{
    init();
}

/**
 * @brief MyMainWindow::init
 */
void MyMainWindow::init()
{
    m_mainWidget = new DWidget ();

    initToolBar();
    m_mainWidget->setStyleSheet("border:1px groove rgba(0, 0, 0, 1);border-radius:0px");

    QVBoxLayout *t_vBoxLayout = new QVBoxLayout(this);
    t_vBoxLayout->addWidget(m_ToolBar);
    DWidget* t_Widget = new DWidget ();

    QHBoxLayout *t_hBoxLayout = new QHBoxLayout();
    m_PlayWidget = new MyPlayWidget ();
    m_PlayWidget->setStyleSheet("border:1px groove rgba(0, 0, 0, 1);border-radius:0px;background-color:rgba(0, 255, 0, 1)");
    m_PlayWidget->setFixedSize(600, 500);

    m_PlayListWidget = new MyPlayListWidget ();
    m_PlayListWidget->setStyleSheet("border:1px groove rgba(0, 0, 0, 1);border-radius:0px;background-color:rgba(0, 0, 255, 1)");
    m_PlayListWidget->setFixedSize(200, 500);

    t_hBoxLayout->addWidget(m_PlayWidget, 0, Qt::AlignLeft);
    t_hBoxLayout->addWidget(m_PlayListWidget, 0, Qt::AlignLeft);
    t_Widget->setLayout(t_hBoxLayout);

    t_vBoxLayout->addWidget(t_Widget);
    m_mainWidget->setLayout(t_vBoxLayout);
    setCentralWidget(m_mainWidget);


}

/**
 * @brief 初始化工具栏
 */
void MyMainWindow::initToolBar()
{
    m_ToolBar = new DToolBar();
    QActionGroup *t_ToolBarActionGroup = new QActionGroup(this);
    QList<QAction*> m_ToolBarList;

    QAction* m_ActionToolBar1 = new QAction(QStringLiteral("视频转码"));
    QAction* m_ActionToolBar2 = new QAction(QStringLiteral("视频分帧"));
    QAction* m_ActionToolBar3 = new QAction(QStringLiteral("字幕识别"));
    m_ActionToolBar1->setCheckable(true);
    m_ActionToolBar2->setCheckable(true);
    m_ActionToolBar3->setCheckable(true);
    m_ToolBarList.append(m_ActionToolBar1);
    m_ToolBarList.append(m_ActionToolBar2);
    m_ToolBarList.append(m_ActionToolBar3);
    t_ToolBarActionGroup->addAction(m_ActionToolBar1);
    t_ToolBarActionGroup->addAction(m_ActionToolBar2);
    t_ToolBarActionGroup->addAction(m_ActionToolBar3);

    m_ToolBar->addActions(m_ToolBarList);
    m_ToolBar->setStyleSheet("background-color:rgb(200,40,43);color:rgb(204,204,204)");

}
