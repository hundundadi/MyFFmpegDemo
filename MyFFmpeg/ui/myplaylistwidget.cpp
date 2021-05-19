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
#include "myplaylistwidget.h"

MyPlayListWidget::MyPlayListWidget()
{
    initUi();
}

void MyPlayListWidget::initUi()
{
    QVBoxLayout *tVBoxLayout = new QVBoxLayout();


    m_playListView = new DListView();
    m_playListView->setFrameShape(QFrame::Shape::NoFrame);
    m_playListView->setEditTriggers(QListView::NoEditTriggers);
    m_playListView->setResizeMode(QListView::Adjust);
    m_playListView->setAutoScroll(true);

    m_playListView->setBackgroundRole(QPalette::Midlight);
    m_playListView->setAutoFillBackground(true);
    QStandardItemModel *tItemModel = new QStandardItemModel();

    DStandardItem *tItem1 = new DStandardItem(QIcon::fromTheme(":/images/ok.svg"),tr("视频一"));
    tItemModel->appendRow(tItem1);
    DStandardItem *tItem2 = new DStandardItem(QIcon::fromTheme(":/images/ok.svg"),tr("视频二"));
    tItemModel->appendRow(tItem2);

    m_playListView->setModel(tItemModel);
    DWidget *tWidgetAdd = new DWidget();
    QHBoxLayout *tWidgetHBoxLayout = new QHBoxLayout();
    DCommandLinkButton *tDCommandLinkButton = new DCommandLinkButton(tr("添加视频"));
    DIconButton *tDIconButton = new DIconButton(nullptr);
    tDIconButton->setIcon(QIcon(":/images/ok.svg"));
    tDIconButton->setFlat(true);
    tWidgetHBoxLayout->setAlignment(Qt::AlignCenter);
    tWidgetHBoxLayout->addWidget(tDCommandLinkButton);
    tWidgetHBoxLayout->addWidget(tDIconButton);

    tWidgetAdd->setLayout(tWidgetHBoxLayout);
    m_playListView->addFooterWidget(tWidgetAdd);

    tVBoxLayout->addWidget(m_playListView);
    this->setLayout(tVBoxLayout);











}
