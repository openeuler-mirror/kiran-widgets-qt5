/**
 * Copyright (c) 2020 ~ 2025 KylinSec Co., Ltd.
 * kiranwidgets-qt5 is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 * Author:     liuxinhao <liuxinhao@kylinsec.com.cn>
 */

#include <QBoxLayout>
#include <QPushButton>
#include <QSet>
#include <QTest>
#include <QThread>

#include "kiran-image-selector/kiran-image-selector.h"

const int default_delay = 300;

class KiranImageSelectorTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase()
    {
        QDir dir("/usr/share/backgrounds/kiran/");
        QStringList filenames = dir.entryList(QDir::NoSymLinks | QDir::Files);
        QStringList files;
        foreach (const QString& fileName, filenames)
        {
            QString filePath = "/usr/share/backgrounds/kiran/" + fileName;
            imagesList << filePath;
        }

        widget = new QWidget();
        widget->resize(300, 120);
        layout = new QVBoxLayout(widget);
        imageSelector = new KiranImageSelector;
        layout->addWidget(imageSelector);

        widget->show();
        QCOMPARE(QTest::qWaitForWindowExposed(widget), true);
    }

    void testAddImage()
    {
        foreach (const QString& path, imagesList)
        {
            QCOMPARE(imageSelector->addImage(path), true);
        }
    }

    void testItemSpacing()
    {
        QList<quint64> itemSpacingSet = {5, 10, 15, 20, 25, 50, 100, 150, 300, 10};
        foreach (const quint64& spacing, itemSpacingSet)
        {
            imageSelector->setItemSpacing(spacing);
            QCOMPARE(imageSelector->itemSpacing(), spacing);
            QTest::qWait(default_delay);
        }
    }

    void testResize()
    {
        qreal maxFactor = 3.0;
        qreal curFactor = 1.0;
        QSize normalSize = imageSelector->size();
        while (curFactor <= maxFactor)
        {
            curFactor += 0.2;
            widget->resize(normalSize * curFactor);
            QTest::qWait(default_delay);
        }

        widget->resize(normalSize);
        QTest::qWait(default_delay);
    }

    void testSelectedImage()
    {
        foreach (const QString& path, imagesList)
        {
            imageSelector->setSelectedImage(path);
            QCOMPARE(imageSelector->selectedImage(), path);
        }
    }

    void testNextButton()
    {
        QPushButton* btn_next = imageSelector->findChild<QPushButton*>("image_selector_next");

        while (btn_next && btn_next->isEnabled() && btn_next->isVisible())
        {
            QTest::mouseClick(btn_next, Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(), default_delay);
        }

        QVERIFY(true);
    }

    void testPrevButton()
    {
        QPushButton* btn_prev = imageSelector->findChild<QPushButton*>("image_selector_prev");

        while (btn_prev && btn_prev->isEnabled() && btn_prev->isVisible())
        {
            QTest::mouseClick(btn_prev, Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(), default_delay);
        }

        QVERIFY(true);
    }

    void testDeleteImage()
    {
        int count = imagesList.count();
        foreach (const QString& path, imagesList)
        {
            imageSelector->removeImage(path);
            QCOMPARE(imageSelector->imageList().size(), --count);
            QTest::qWait(default_delay);
        }
    }

    void cleanupTestCase()
    {
        delete imageSelector;
        delete widget;
    }

private:
    QWidget* widget;
    QBoxLayout* layout;
    KiranImageSelector* imageSelector;
    QStringList imagesList;
};

QTEST_MAIN(KiranImageSelectorTest)
#include "kiran-image-selector-test.moc"