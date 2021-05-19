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
#ifndef MYPLAYWIDGET_H
#define MYPLAYWIDGET_H
#include <DSlider>
#include <DMainWindow>
#include <DWidget>
#include <DLabel>
#include <DLineEdit>
#include <QHBoxLayout>
#include <QDebug>

DWIDGET_USE_NAMESPACE

/**
 * @brief 此类是播放窗口，调用ffpaly实现
 */
class MyPlayWidget : public DWidget
{
public:
    MyPlayWidget();
};

#endif // MYPALYWIDGET_H
