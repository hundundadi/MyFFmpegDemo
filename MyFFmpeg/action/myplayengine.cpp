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

#define MAX_AUDIO_FRAME_SIZE 192000 // 1 second of 48khz 32bit audio



/***    MyPlayEngine     ***/

MyPlayEngine::MyPlayEngine()
{

    m_avDemuxThread = new MyAVDemuxThread ();
    m_audioPlayThread = new MyAudioPlayThread (this);

    //链接信号 更新视频中的每一张图片与播放引擎的播放每张图片
    connect(m_avDemuxThread,&MyAVDemuxThread::updateVideoPic,this,&MyPlayEngine::showOneFram);
    //链接音频线程 更新播放声音
    connect(m_avDemuxThread,&MyAVDemuxThread::updateAudioData,m_audioPlayThread,&MyAudioPlayThread::updateAudioData);
    connect(m_avDemuxThread,&MyAVDemuxThread::finished,m_avDemuxThread,&MyAVDemuxThread::deleteLater);
    connect(m_audioPlayThread,&MyAudioPlayThread::finished,m_audioPlayThread,&MyAudioPlayThread::deleteLater);

}

MyPlayEngine::~MyPlayEngine()
{

}

/**
 * @brief 播放视频
 * @param 视频的路径
 */
void MyPlayEngine::playVideo(const QString videoPath)
{

    if(m_avDemuxThread->playVideo(videoPath)) m_audioPlayThread->start();
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

/**
 * @brief 初始化解复用器
 */
void MyAVDemuxThread::initMyAVDemux()
{

    avformat_network_init();
}
/**
 * @brief 开始播放视频
 * @param 视频的路径
 * @return 播放是否成功，路径是否有问题
 */
bool MyAVDemuxThread::playVideo(const QString videoPath)
{

    if(videoPath.isNull()||videoPath.isEmpty()) return false;
    m_videoFileName = videoPath;
    start();
    return true;
}

/**
 * @brief 播放线程开始运行
 */
void MyAVDemuxThread::run()
{
    qDebug() << __TIME__ << __FUNCTION__ << __LINE__ << "播放开始！";
    AVFormatContext *avFormatContext = nullptr;    //一个视频文件的总数据
    AVPacket packet;                               //压缩后的数据（视频对应H.264等码流数据，音频对应AAC/MP3等码流数据）
    AVFrame *pFrame = nullptr;                     //未压缩后的数据（视频对应RGB/YUV像素数据，音频对应PCM采样数据）
    int audioStream = -1;
    int videoStream = -1;
    int err = -1;

    //初始化
    avFormatContext = avformat_alloc_context();
    if(!avFormatContext)
    {
        qDebug() << "不能初始化，无法分配 avFormatContext !";
        return;
    }

    //打开文件并读取报头
    if(avformat_open_input(&avFormatContext,m_videoFileName.toLatin1().data(),nullptr,nullptr) != 0)
    {
        qDebug() << "不能初始化，无法分配 avFormatContext !";
        return;
    }

    //判断报头中是否包含有流
    if(avformat_find_stream_info(avFormatContext,nullptr) < 0)
    {
        qDebug() << "不能找到流信息！";
        return;
    }

    //遍历报头中的流,找出其中的音频流与视频流在流中的索引
    for(unsigned int i=0;i < avFormatContext->nb_streams; i++)
    {
        //获取流中音频流的index
        if(avFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            audioStream = static_cast<int>(i);
        }
        //获取流中视频流的index
        else if(avFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoStream = static_cast<int>(i);
        }
    }

    //判断音视频流是否存在
    if(audioStream == -1 && videoStream == -1)
    {
        qDebug() << "未找到任何视频流和音频流！";
        return;
    }

    //原始码流的初始化，原始码流：未压缩的数据（视频对应RGB/YUV像素数据，音频对应PCM采样数据）
    pFrame = av_frame_alloc();

    //音频解码
    AVCodecContext *pCodecCtxAudio = nullptr;   //音频编解码码报文
    AVCodec        *pCodecAudio;                //音频编解码器
    uint8_t        *audioBuffer = nullptr;      //
    struct SwrContext *au_convert_ctx = nullptr;//音频重采样上下文
    int out_buffer_size = 0;                    //
    if(audioStream != -1)
    {
        //初始化
        pCodecCtxAudio =  avcodec_alloc_context3(nullptr);
        if(!pCodecCtxAudio)
        {
            qDebug() << "音频编解码报文初始化失败！";
            return;
        }

        //音频编解码器设置,将音频中之前的编码器参数设置给音频编解码报文
        err = avcodec_parameters_to_context(pCodecCtxAudio,avFormatContext->streams[audioStream]->codecpar);
        if(err < 0)
        {
            qDebug() << "将音频中之前的编码器设置给音频编解码报文失败！";
            return;
        }

        //根据编码器找出相应的解码器
        pCodecAudio = avcodec_find_decoder(pCodecCtxAudio->codec_id);
        if(pCodecAudio == nullptr)
        {
            qDebug() << "未找到对应的音频解码器！";
            return;
        }

        //打开编解码器
        if(avcodec_open2(pCodecCtxAudio,pCodecAudio,nullptr) < 0)
        {
            qDebug() << "不能打开对应的编解码器！";
            return;
        }

        //音频输出的参数
        uint64_t out_channel_layout = AV_CH_LAYOUT_STEREO; //双声道
        //nb_samples:AAC-1024  MP3-1152
        //获取音频帧中每个通道的采样数。
        int out_nb_samples = pCodecCtxAudio->frame_size;
        AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;
        //采样率
        int out_sample_rate = 44100;
        //获取通道数量 返回通道布局中的通道数。
        int out_channels = av_get_channel_layout_nb_channels(out_channel_layout);

        //为给定的音频参数获取所需的缓冲区大小。
        out_buffer_size = av_samples_get_buffer_size(nullptr,out_channels,out_nb_samples,out_sample_fmt,1);

        //返回给定通道数量的默认通道布局。
        int64_t in_channel_layout = av_get_default_channel_layout(pCodecCtxAudio->channels);

        //分配一个适合所有内存访问的对齐内存块(包括CPU上可用的向量)。
        audioBuffer = (uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE * 2);

        //ffmpeg中刚刚解码出的数据因为排列方式的原因，不能直接播放，必须要转换
        //分配SwrContext
        au_convert_ctx = swr_alloc();
        //设置公共参数
        au_convert_ctx = swr_alloc_set_opts(au_convert_ctx,
                                            out_channel_layout,
                                            out_sample_fmt,
                                            out_sample_rate,
                                            in_channel_layout,
                                            pCodecCtxAudio->sample_fmt,
                                            pCodecCtxAudio->sample_rate,
                                            0,
                                            nullptr);
        //在设置用户参数后初始化上下文。
        swr_init(au_convert_ctx);
    }

    //视频解码
    AVCodecContext *pVideoCodecContext = nullptr;   //视频编解码报文
    AVCodec        *pCodecVideo;                    //视频编解码器
    AVCodecParameters *pVideoChannelCodecPara = nullptr; //视频编解码参数
    struct SwsContext *img_convert_ctx = nullptr;   //图片重采样报文
    struct SwsContext *img_convert_ctx_rgb = nullptr;  //rgb格式图片重采样
    AVFrame *pFrameYUV = nullptr;                   //YUV原始码流
    AVFrame *pFrameRGB = nullptr;                   //RGB原始码流
    int iWindowWidth = 0;
    int iWindowHeight = 0;
    unsigned char *rgbBuffer;
    unsigned char *yuvBuffer;

    if(videoStream != -1)
    {
        //获取视频编码的参数
        pVideoChannelCodecPara = avFormatContext->streams[videoStream]->codecpar;
        //初始化视频编解码器
        pVideoCodecContext = avcodec_alloc_context3(nullptr);
        if(!pVideoCodecContext)
        {
            qDebug() << "初始化视频编解码器失败！";
            return;
        }

        //视频编解码器设置,将视频中之前的编码器参数设置给视频编解码报文
        err = avcodec_parameters_to_context(pVideoCodecContext,pVideoChannelCodecPara);
        if(err < 0)
        {
            qDebug() << "将视频中之前的编码器参数设置给视频编解码报文失败";
            return;
        }

        //根据视频的编码器查找相应的解码器
        pCodecVideo = avcodec_find_decoder(pVideoChannelCodecPara->codec_id);
        if(pCodecVideo == nullptr)
        {
            qDebug() << "未找到响应的解码器";
            return;
        }

        //打开编解码器
        err = avcodec_open2(pVideoCodecContext,pCodecVideo,nullptr);
        if(err)
        {
            qDebug() << "打开响应的编解码器失败！";
            return;
        }

        iWindowWidth = pVideoCodecContext->width;
        iWindowHeight = pVideoCodecContext->height;

        //获取图片重采样报文分配并返回一个SwsContext。您需要它来使用sws_scale()执行缩放/转换操作。
        img_convert_ctx = sws_getContext(pVideoCodecContext->width,
                                         pVideoCodecContext->height,
                                         pVideoCodecContext->pix_fmt,
                                         pVideoCodecContext->width,
                                         pVideoCodecContext->height,
                                         AV_PIX_FMT_YUV420P,
                                         SWS_BICUBIC,
                                         nullptr,
                                         nullptr,
                                         nullptr);

        img_convert_ctx_rgb = sws_getContext(pVideoCodecContext->width,
                                             pVideoCodecContext->height,
                                             AV_PIX_FMT_YUV420P,
                                             pVideoCodecContext->width,
                                             pVideoCodecContext->height,
                                             AV_PIX_FMT_RGB32,
                                             SWS_BICUBIC,
                                             nullptr,
                                             nullptr,
                                             nullptr);
        pFrameYUV = av_frame_alloc();
        pFrameRGB = av_frame_alloc();

        //计算一个标准画面的大小
        yuvBuffer = static_cast<unsigned char *>(av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P,
                                                                        pVideoCodecContext->width,
                                                                        pVideoCodecContext->height,
                                                                        1)));
        rgbBuffer = static_cast<unsigned char *>(av_malloc(av_image_get_buffer_size(AV_PIX_FMT_RGB32,
                                                                        pVideoCodecContext->width,
                                                                        pVideoCodecContext->height,
                                                                        1
                                                                        )));
        //根据指定的图像参数和提供的数组设置数据指针和行大小
        av_image_fill_arrays(pFrameYUV->data,pFrameYUV->linesize,yuvBuffer,AV_PIX_FMT_YUV420P,pVideoCodecContext->width,pVideoCodecContext->height,1);
        av_image_fill_arrays(pFrameRGB->data,pFrameRGB->linesize,rgbBuffer,AV_PIX_FMT_RGB32,pVideoCodecContext->width,pVideoCodecContext->height,1);
    }

    //打印有关输入或输出格式的详细信息，如持续时间、比特率、流、容器、程序、元数据、侧数据、编解码器和时间基。
    qDebug() << "--------------- File Information ----------------";
    av_dump_format(avFormatContext,0,m_videoFileName.toLatin1().data(),false);
    qDebug() << "-------------------------------------------------";

    //遍历流，返回流的下一帧。
    while (av_read_frame(avFormatContext,&packet) >= 0)
    {
        if(packet.stream_index == audioStream)
        {
            int got_fram = 0;
            //解码音频
            err = avcodec_decode_audio4(pCodecCtxAudio,pFrame,&got_fram,&packet);
            if(err < 0)
            {
                qDebug() << "解码音频帧失败！";
                return;
            }
            if(got_fram > 0)
            {
                //转换音频
                swr_convert(au_convert_ctx,&audioBuffer,MAX_AUDIO_FRAME_SIZE,(const uint8_t **)pFrame->data,pFrame->nb_samples);

                QByteArray audio;
                audio.append((char*)audioBuffer,out_buffer_size);
                emit updateAudioData(audio);
            }else
            {
                qDebug()<< "没有音频数据！";
            }
        }
        else if(packet.stream_index == videoStream)
        {
            //向解码器提供原始数据包数据作为输入
            err = avcodec_send_packet(pVideoCodecContext,&packet);
            if(err != 0)
            {
                if(AVERROR(EAGAIN) == err)
                {
                    continue;
                }
                qDebug() << "发送视频帧失败！" << err;
            }
            //解码视频
            //从解码器返回解码的输出数据。
            while(avcodec_receive_frame(pVideoCodecContext,pFrame) == 0)
            {
                //缩放图片
                sws_scale(img_convert_ctx,pFrame->data,pFrame->linesize,0,pVideoCodecContext->height,pFrameYUV->data,pFrameYUV->linesize);
                //qDebug() << "img_convert_ctx_rgb: " << img_convert_ctx_rgb;
                if(img_convert_ctx_rgb)
                {
                    sws_scale(img_convert_ctx_rgb,pFrameYUV->data,pFrameYUV->linesize,0,pVideoCodecContext->height,pFrameRGB->data,pFrameRGB->linesize);
                    QImage image((uchar *)pFrameRGB->data[0],iWindowWidth,iWindowHeight,QImage::Format_ARGB32);
                    emit updateVideoPic(image);
                }
            }
        }

    }

    avformat_close_input(&avFormatContext);
    qDebug() << "播放结束！";

}

/***    MyAVDemuxThread     ***/

/***    MyAudioPlayThread     ***/
const int g_bufferSize = 44100*10000;
int g_CurrentRead = 0;
int g_CurrentWrite = 0;
char g_buffer[g_bufferSize];
QSemaphore freeBytes(g_bufferSize);
QSemaphore usedBytes;
MyAudioPlayThread::MyAudioPlayThread(QObject *parent):
    QThread (parent),
    m_audioOutput(nullptr),
    m_audioOutDevice(nullptr),
    m_buf(nullptr),
    m_index(0)
{
    //返回默认输出音频设备的信息。所有的平台和音频插件实现都提供了默认的音频设备来使用
    initializeAudio(QAudioDeviceInfo::defaultInputDevice());
}

void MyAudioPlayThread::initializeAudio(const QAudioDeviceInfo &deviceInfo)
{
    if(m_audioOutput)
    {
        m_audioOutput->stop();
        delete m_audioOutput;
        m_audioOutput = nullptr;
    }

    if(m_audioOutDevice)
    {
        m_audioOutDevice->close();
        delete m_audioOutDevice;
        m_audioOutDevice = nullptr;
    }

    //配置音频格式
    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    if(!deviceInfo.isFormatSupported(format))
    {
        qDebug() << "音频设备不支持当前格式！请重新设置格式";
        //自动将当前格式匹配到当前音频设备支持的格式
        format = deviceInfo.nearestFormat(format);
    }

    //m_audioOutput = new QAudioOutput(deviceInfo,format);
    m_audioOutput = new QAudioOutput(format);
    //qDebug() << __LINE__ << deviceInfo.isNull() << deviceInfo.deviceName();
    m_audioOutDevice = m_audioOutput->start();
    //qDebug() << __LINE__;

    int bf = m_audioOutput->bytesFree();
    if(!m_buf)
    {
        m_buf = new char [bf * 2000];
    }
    memset(m_buf, 0, bf * 2000);
    m_index = 0;

}

void MyAudioPlayThread::updateAudioData(QByteArray audio)
{
    int out_buffer_size = audio.size();
    //尝试从freeBytes获取out_buffer_size个由信号量保护的资源，成功后返回true
    if(freeBytes.tryAcquire(out_buffer_size))
    {
        //从audio.constData()内存中复制out_buffer_size个数据到g_buffer + g_CurrentWrite内存区域
        memcpy(g_buffer + g_CurrentWrite,audio.constData(),out_buffer_size);
        g_CurrentWrite += out_buffer_size;
        g_CurrentWrite = g_CurrentWrite % g_bufferSize;
        //释放out_buffer_size个由信号量保护的资源
        usedBytes.release(out_buffer_size);
    }

}

void MyAudioPlayThread::run()
{
    while (1)
    {
        //音频缓冲区中可用的字节数/周期
        int chunks = m_audioOutput->bytesFree() / m_audioOutput->periodSize();
        while(chunks)
        {
            int len = m_audioOutput->periodSize();
            if(usedBytes.tryAcquire(len))
            {
                m_audioOutDevice->write(g_buffer+g_CurrentRead,len);
                g_CurrentRead += len;
                g_CurrentRead = g_CurrentRead % g_bufferSize;
                freeBytes.release();
            }
            --chunks;
        }
    }

}



/***    MyAudioPlayThread     ***/

