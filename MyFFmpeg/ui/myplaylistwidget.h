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
#include <DFileDialog>
#include <DMessageBox>
#include <QHBoxLayout>
#include <QDebug>
#include <QIcon>

DWIDGET_USE_NAMESPACE

/**
 * @brief 此类是播放列表窗口
 */
class MyPlayListWidget : public DWidget
{
    Q_OBJECT
public:
    MyPlayListWidget();
    /**
     * @brief 获取当前选中的视频名称
     * @return
     */
    QString getCurrentFile();

signals:

    void playFile(QString currentFile);

private slots:
    /**
     * @brief 将打开的文件添加到播放列表
     * @return
     */
    bool addVideoForPlayList();

    /**
     * @brief 显示点击的项
     * @param 点击项的index
     */
    void showClick(QModelIndex index);



private:

    /**
     * @brief 初始化界面
     */
    void initUi();

    /**
     * @brief 打开文件
     * @return 选择的文件
     */
    QStringList openFiles();

    /**
     * @brief 添加播放列表
     */
    bool apendPlayListView();



    int m_iNum = 2;
    DListView *m_playListView;


    /**
     * @brief 播放列表 key播放文件 value缩略图
     */
    QMap<QString,QString> m_playFileMap;

    QString m_currentFile;


};

#endif // MYPLAYLISTWIDGET_H
