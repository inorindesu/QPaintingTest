// 
// QPaintingTest/MainWindow.cpp 
//
// Copyright (C) 2013  Inori Sakura <inorindesu@gmail.com>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or (at
// your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// 


#include "MainWindow.hpp"
#include <QTime>
#include <QImage>

MainWindow::MainWindow()
{
  this->_isGl = false;
  QWidget* w = new QWidget();

  this->_testWidget = new Widget();
  QObject::connect(this->_testWidget, SIGNAL(paint(QPainter*)), this, SLOT(paintSquare(QPainter*)));
  this->_lblFps = new QLabel("");
  this->_btnSwitch = new QPushButton("Switch to Gl");
  QObject::connect(this->_btnSwitch, SIGNAL(clicked()), this, SLOT(switchWidget()));
  
  QVBoxLayout* l = new QVBoxLayout();
  l->addWidget(this->_testWidget, 1);
  l->addWidget(this->_lblFps);
  l->addWidget(this->_btnSwitch);
  w->setLayout(l);
  this->setCentralWidget(w);
  this->startTimer(0);
  this->_testWidget->resize(640, 480);
  this->resize(800, 600);
  this->_frameCount = 0;
  this->_start = QTime::currentTime();
}

void MainWindow::switchWidget()
{
  QWidget* wOld = this->centralWidget();
  QVBoxLayout* l = new QVBoxLayout();
  delete wOld->layout();
  delete this->_testWidget;
  if(this->_isGl)
    {
      this->_btnSwitch->setText("Switch to Gl");
      this->_testWidget = new Widget();
      this->_isGl = false;
    }
  else
    {
      this->_btnSwitch->setText("Switch to Normal");
      this->_testWidget = new GlWidget();
      this->_isGl = true;
    }
  QObject::connect(this->_testWidget, SIGNAL(paint(QPainter*)), this, SLOT(paintSquare(QPainter*)));
  this->_testWidget->resize(640, 480);
  l->addWidget(this->_testWidget, 1);
  l->addWidget(this->_lblFps);
  l->addWidget(this->_btnSwitch);
  wOld->setLayout(l);
  this->_frameCount = 0;
  this->_start = QTime::currentTime();
}

void MainWindow::paintSquare(QPainter* p)
{
  p->save();
  qsrand(QTime::currentTime().msec());

  QImage img(32, 32, QImage::Format_ARGB32_Premultiplied);
  //QPixmap img(32, 32);
  QPainter* p2 = new QPainter(&img);
  p2->fillRect(0, 0, 32, 32, QColor(255, 255, 192));
  delete p2;
  
  for(int i = 0; i < repeatCount; i++)
    {
      int x = qrand() % 640;
      int y = qrand() % 480;

      // 這個很慢
      //p->fillRect(x, y, 32, 32, Qt::darkGreen);

      // 使用pixmap和image沒有很明顯的差異
      p->drawImage(x, y, img);
      //p->drawPixmap(x, y, img);
      p->drawText(x, y, 32, 32, Qt::AlignHCenter | Qt::AlignVCenter, QString(1, QChar(0x5b57)));
    }
  this->_frameCount += 1;
  qreal fps = this->_frameCount * 1000 / (qreal)this->_start.msecsTo(QTime::currentTime());
  this->_lblFps->setText(QString("FPS: %1").arg(fps));
  p->restore();
}

void MainWindow::timerEvent(QTimerEvent* e)
{
  this->_testWidget->update();
}
