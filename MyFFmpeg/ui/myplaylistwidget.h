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
#ifndef MYPLAYLISTWIDGET_H
#define MYPLAYLISTWIDGET_H
#include <DWidget>
#include <DListView>
#include <DCommandLinkButton>
#include <DIconButton>

#include <QHBoxLayout>
#include <QDebug>
#include <QIcon>

DWIDGET_USE_NAMESPACE

/**
 * @brief 此类是播放列表窗口
 */
class MyPlayListWidget : public DWidget
{
public:
    MyPlayListWidget();

private:

    /**
     * @brief 初始化界面
     */
    void initUi();

    int m_iNum = 2;
    DListView *m_playListView;



};

#endif // MYPLAYLISTWIDGET_H
