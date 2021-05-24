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
//本项目的文件
#include "ui/myplaylistwidget.h"
#include "ui/myplaywidget.h"
#include "action/myplayengine.h"

//dtk的类
#include <DSlider>
#include <DMainWindow>
#include <DWidget>
#include <DLabel>
#include <DLineEdit>
#include <QHBoxLayout>
#include <QDebug>

//qt的类
#include <QPoint>
#include <QPainter>
//其他库
extern "C"{
#include <libavformat/avformat.h>
#include <libavutil/display.h>
#include <libavutil/avutil.h>
}
//cpp标准库

//linux系统库

DWIDGET_USE_NAMESPACE

/**
 * @brief 此类是播放窗口，调用ffpaly实现
 */
class MyPlayWidget : public DWidget
{
    Q_OBJECT
public:
    MyPlayWidget();

public slots:
    /**
     * @brief 在界面显示每一帧图片
     * @param 每一帧图片
     */
    void showOneFram(QImage img);

protected:
    /**
     * @brief 重绘界面
     */
    void paintEvent(QPaintEvent *);


private :
    /**
     * @brief 播放引擎
     */
    MyPlayEngine* m_playEngine;

    /**
     * @brief 每一帧图片
     */
    QImage m_image;
};


#endif // MYPLAYWIDGET_H
