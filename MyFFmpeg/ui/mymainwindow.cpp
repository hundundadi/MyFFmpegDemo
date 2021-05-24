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

MyMainWindow::MyMainWindow()
{
    init();
}

/**
 * @brief MyMainWindow::init
 */
void MyMainWindow::init()
{
    titlebar()->setTitle("MyFFmpegDemo"); //让标题栏无文字内容显示

    m_mainWidget = new DWidget ();

    initToolBar();
    m_mainWidget->setStyleSheet("border:1px groove rgba(0, 0, 0, 1);border-radius:0px");

    QVBoxLayout *t_vBoxLayout = new QVBoxLayout(this);
    t_vBoxLayout->addWidget(m_ToolBar);
    DWidget* t_Widget = new DWidget ();

    QHBoxLayout *t_hBoxLayout = new QHBoxLayout();
    initPlayWidget();

    initPlayListWidget();

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
    QAction* m_ActionToolBar4 = new QAction(QStringLiteral("图像滤波"));
    m_ActionToolBar1->setCheckable(true);
    m_ActionToolBar2->setCheckable(true);
    m_ActionToolBar3->setCheckable(true);
    m_ActionToolBar4->setCheckable(true);
    m_ToolBarList.append(m_ActionToolBar1);
    m_ToolBarList.append(m_ActionToolBar2);
    m_ToolBarList.append(m_ActionToolBar3);
    m_ToolBarList.append(m_ActionToolBar4);
    t_ToolBarActionGroup->addAction(m_ActionToolBar1);
    t_ToolBarActionGroup->addAction(m_ActionToolBar2);
    t_ToolBarActionGroup->addAction(m_ActionToolBar3);
    t_ToolBarActionGroup->addAction(m_ActionToolBar4);

    m_ToolBar->addActions(m_ToolBarList);
    m_ToolBar->setStyleSheet("background-color:rgb(200,40,43);color:rgb(204,204,204)");

}

/**
 * @brief 初始化播放窗口
 */
void MyMainWindow::initPlayWidget()
{
    m_PlayWidget = new MyPlayWidget ();
    m_PlayWidget->setStyleSheet("border:1px groove rgba(0, 0, 0, 1);border-radius:0px;background-color:rgba(0, 255, 0, 1)");
    m_PlayWidget->setFixedSize(600, 500);
}

/**
 * @brief 初始化播放列表窗口
 */
void MyMainWindow::initPlayListWidget()
{
    m_PlayListWidget = new MyPlayListWidget ();
    m_PlayListWidget->setStyleSheet("border:1px groove rgba(0, 0, 0, 1);border-radius:0px;background-color:rgba(0, 0, 255, 1)");
    m_PlayListWidget->setFixedSize(200, 500);

}

/**
 * @brief 调用播放引擎播放视频
 */
void MyMainWindow::playAV()
{

    QString currentFile = m_PlayListWidget->getCurrentFile();

    m_playEngine->playVideo(currentFile);

}
