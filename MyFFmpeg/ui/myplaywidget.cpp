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
#include "myplaywidget.h"

MyPlayWidget::MyPlayWidget()
{
    this->setStyleSheet("border:1px groove rgba(0, 0, 0, 1);border-radius:0px;background-color:rgba(0, 255, 0, 1)");
    this->setFixedSize(600, 500);
}

void MyPlayWidget::showOneFram(QImage img)
{
    m_image = img;
    //激活重绘事件
    update();
}

void MyPlayWidget::paintEvent(QPaintEvent *)
{
    if(0 >= m_image.size().width()) return;
    QPainter painter(this);
    //将图片缩放为窗口大小
    QImage img = m_image.scaled(this->size(),Qt::IgnoreAspectRatio);
    int x = this->width() - img.width();
    int y = this->height() - img.height();
    painter.drawImage(QPoint(x,y),img);

}
