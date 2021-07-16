 /**
  * @Copyright (C) 2020 ~ 2021 KylinSec Co., Ltd.
  *
  * Author:     liuxinhao <liuxinhao@kylinos.com.cn>
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program; If not, see <http: //www.gnu.org/licenses/>. 
  */

#ifndef KIRANIMAGESELECTOR_KIRAN_IMAGE_LOAD_MANAGER_H
#define KIRANIMAGESELECTOR_KIRAN_IMAGE_LOAD_MANAGER_H

#include <QObject>
#include <QQueue>
#include <QFutureWatcher>
#include <QSize>
#include <QPixmap>

class KiranImageLoadManager : public QObject {
Q_OBJECT
private:
    KiranImageLoadManager(QObject *parent = nullptr);
    void init();

public:
    static KiranImageLoadManager *instance();
    ~KiranImageLoadManager();

    /* 加载指定路径图片，转换成指定大小,生成任务加入队列 */
    void load(QString imagePath, QSize size);
    /* 停止当前的加载任务并删除所有的加载任务 */
    void reset();

private slots:
    /* QFutureWatcher finished槽函数 */
    void onLoadFinished();

signals:
    /**
     * @brief 图片加载完成信号
     * @param imagePath 加载完成的图片位置
     * @param fitSize   适用于哪个大小的图片项
     * @param pixmap    加载完成的图片
     */
    void imageLoaded(QString imagePath, QSize fitSize, QPixmap pixmap);

private:
    /**
     * @brief 异步加载图片的实现函数,通过QtConcurrent::run在线程中异步执行
     * @param imagePath 图片位置
     * @param size      需要保持比例拉伸匹配什么大小
     * @return 加载和拉伸之后的图片,可通过std::move直接以避免内存拷贝
     */
    static QPixmap loadPixmap(QString imagePath, QSize size);
    QString getCacheFilePath(QString imagePath, QSize size);
    void handlerNextLoadReq();

private:
    QQueue<QPair<QString, QSize>> m_loadReqQueue;
    QFutureWatcher<QPixmap> m_loadFutureWatcher;
};

#endif //KIRANIMAGESELECTOR_KIRAN_IMAGE_LOAD_MANAGER_H
