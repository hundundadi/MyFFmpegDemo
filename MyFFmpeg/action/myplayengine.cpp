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
#include "myplayengine.h"

/***    MyPlayEngine     ***/

MyPlayEngine::MyPlayEngine()
{
    m_avDemuxThread = new MyAVDemuxThread ();
    m_audioPlayThread = new MyAudioPlayThread ();

    //链接信号 更新视频中的每一张图片与播放引擎的播放每张图片
    connect(m_avDemuxThread,&MyAVDemuxThread::updateVideoPic,this,&MyPlayEngine::showOneFram);
    connect(m_avDemuxThread,&MyAVDemuxThread::updateAudioData,m_audioPlayThread,&MyAudioPlayThread::updateAudioData);
    connect(m_avDemuxThread,&MyAVDemuxThread::finished,m_avDemuxThread,&MyAVDemuxThread::deleteLater);
    connect(m_audioPlayThread,&MyAudioPlayThread::finished,m_audioPlayThread,&MyAudioPlayThread::deleteLater);

}

/**
 * @brief 播放视频
 * @param 视频的路径
 */
void MyPlayEngine::playVideo(const QString videoPath)
{
    m_avDemuxThread->playVideo(videoPath);
    m_audioPlayThread->start();
}

/***    MyPlayEngine     ***/

/***    MyAVDemuxThread     ***/

MyAVDemuxThread::MyAVDemuxThread()
{

    initMyAVDemux();
}

MyAVDemuxThread::~MyAVDemuxThread()
{

    //ffmpeg释放
    avformat_network_deinit();

    qDebug()<<"thread quit()";

}

void MyAVDemuxThread::initMyAVDemux()
{

}

void MyAVDemuxThread::playVideo(const QString videoPath)
{

}

void MyAVDemuxThread::run()
{

}

/***    MyAVDemuxThread     ***/

/***    MyAudioPlayThread     ***/

MyAudioPlayThread::MyAudioPlayThread()
{

}

void MyAudioPlayThread::updateAudioData(QByteArray audio)
{

}

void MyAudioPlayThread::run()
{

}

void MyAudioPlayThread::initializeAudio(const QAudioDeviceInfo &deviceInfo)
{

}

/***    MyAudioPlayThread     ***/

