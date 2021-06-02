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
#ifndef MYPLAYENGINE_H
#define MYPLAYENGINE_H

//本项目的文件

//dtk的类

//qt的类
#include <QThread>
#include <QImage>
#include <QAudioOutput>
#include <QDebug>
#include <QSemaphore>
#include <QException>
#include <QIODevice>

//其他库
#ifdef __cplusplus
extern "C"
{
#endif
#include "libavutil/avstring.h"
#include "libavutil/eval.h"
#include "libavutil/mathematics.h"
#include "libavutil/pixdesc.h"
#include "libavutil/imgutils.h"
#include "libavutil/parseutils.h"
#include "libavutil/samplefmt.h"
#include "libavutil/time.h"
#include "libavdevice/avdevice.h"
#include "libswscale/swscale.h"
#include "libavcodec/avfft.h"
#include "libswresample/swresample.h"


#ifdef __cplusplus
};
#endif


//cpp标准库

//linux系统库


struct playResult {
    bool flag;
    QString message; ///< size left in the buffer
};
/**
 * @brief 视频播放的解复用线程
 */
class MyAVDemuxThread :public QThread
{
    Q_OBJECT
public:
    MyAVDemuxThread();
    ~MyAVDemuxThread();
    /**
     * @brief 播放视频
     * @param 播放文件的路径
     */
    bool playVideo(const QString videoPath);

private :
    /**
     * @brief 初始化解复用器
     */
    void initMyAVDemux();



signals:
    void updateVideoPic(QImage img);
    void updateAudioData(QByteArray audio);

private:
    void run() override;

private:
    QString  m_videoFileName;
};




/**
 * @brief 声音播放线程
 */
class MyAudioPlayThread: public QThread
{

    Q_OBJECT
public:
    MyAudioPlayThread(QObject *parent = nullptr);

public slots:
    void updateAudioData(QByteArray audio);

private:
    void run() override;
    void initializeAudio(const QAudioDeviceInfo &deviceInfo);

private:
    QAudioOutput *m_audioOutput;
    QIODevice *m_audioOutDevice;

    char *m_buf;
    int m_index;

};

/**
 * @brief 播放引擎类，主要用来播放视频
 */
class MyPlayEngine : public QObject
{
    Q_OBJECT
public:
    MyPlayEngine();
    ~MyPlayEngine();

    /**
     * @brief 播放视频
     * @param 播放文件的路径
     */
    void playVideo(const QString videoPath);

private :
    void init();
signals:
    void showOneFram(QImage img);

public slots:

private:

    MyAVDemuxThread *m_avDemuxThread;

    MyAudioPlayThread *m_audioPlayThread;

};

#endif // MYPLAYENGINE_H
