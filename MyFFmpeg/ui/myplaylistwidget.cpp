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
    //初始化Listview
    m_playListView = new DListView();
    m_playListView->setFrameShape(QFrame::Shape::NoFrame);
    m_playListView->setEditTriggers(QListView::NoEditTriggers);
    m_playListView->setResizeMode(QListView::Adjust);
    m_playListView->setAutoScroll(true);
    m_playListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//屏蔽水平滚动条
    m_playListView->setBackgroundRole(QPalette::Midlight);
    m_playListView->setAutoFillBackground(true);

    if(m_playFileMap.empty()){
        m_playFileMap.insert("视频一","/images/ok.svg");
        m_playFileMap.insert("视频二","/images/ok.svg");
    }
    QStandardItemModel *tItemModel = new QStandardItemModel();
    QMap<QString,QString>::Iterator it=m_playFileMap.begin();
    while(it!=m_playFileMap.end())
    {
        DStandardItem *tItem1 = new DStandardItem(QIcon::fromTheme(it.value()),it.key());
        tItemModel->appendRow(tItem1);
        qDebug()<<it.key()<<"\t"<<it.value();
        it++;
    }
    m_playListView->setModel(tItemModel);

    //链接每个item的点击事件
    connect(m_playListView,SIGNAL(clicked(QModelIndex)),this,SLOT(showClick(QModelIndex)));

    DWidget *tWidgetAdd = new DWidget();
    QHBoxLayout *tWidgetHBoxLayout = new QHBoxLayout();
    DCommandLinkButton *tDCommandLinkButton = new DCommandLinkButton(tr("添加视频"));
    connect(tDCommandLinkButton,&DCommandLinkButton::clicked,this,&MyPlayListWidget::addVideoForPlayList);

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

/**
 * @brief 添加视频到播放列表
 * @return 成功返回true，失败返回false
 */
bool MyPlayListWidget::addVideoForPlayList()
{
    QStringList tOpenFiles = openFiles();
    if(0 == tOpenFiles.length()) return false;
    for(QString i_file : tOpenFiles){
        QFileInfo fileInfo(i_file);
        m_playFileMap.insert(fileInfo.fileName(),":images/ok.svg");
        m_playFileMap.keys().sort(Qt::CaseSensitivity::CaseSensitive);
    }
    bool flag = apendPlayListView();
    return flag;
}

/**
 * @brief 打开文件
 * @return 选择的文件
 */
QStringList MyPlayListWidget::openFiles()
{
    DFileDialog *tDFileDialog = new DFileDialog();
    //文件对话框为打开文件类型
    tDFileDialog->setAcceptMode(QFileDialog::AcceptOpen);
    //可同时选择打开多个文件
    tDFileDialog->setFileMode(QFileDialog::ExistingFiles);
    tDFileDialog->show();
    tDFileDialog->exec();
    QStringList tFiles = tDFileDialog->selectedFiles();
    return tFiles;
}

/**
 * @brief 添加播放列表
 */
bool MyPlayListWidget::apendPlayListView()
{
    if(!m_playFileMap.empty()){
        QStandardItemModel *tItemModel = new QStandardItemModel();
        QMap<QString,QString>::Iterator it=m_playFileMap.begin();
        while(it!=m_playFileMap.end())
        {
            DStandardItem *tItem1 = new DStandardItem(QIcon::fromTheme(it.value()),it.key());
            tItemModel->appendRow(tItem1);
            qDebug()<<it.key()<<"\t"<<it.value();
            it++;
        }
        m_playListView->setModel(tItemModel);
        return true;
    }
    return false;
}

/**
 * @brief 显示点击的项
 * @param 点击项的index
 */
void MyPlayListWidget::showClick(QModelIndex index)
{
    QString strTemp;
    strTemp = index.data().toString();
    m_currentFile = index.data().toString();
    DMessageBox msg;
    msg.setText(strTemp);
    msg.exec();
    emit playFile();

}

QString MyPlayListWidget::getCurrentFile()
{
    return m_currentFile;
}



