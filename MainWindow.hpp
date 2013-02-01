//
// QPaintingTest/MainWindow.hpp
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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Widget.hpp"
#include "GlWidget.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QTimerEvent>
#include <QPushButton>
#include <QTime>

class MainWindow: public QMainWindow
{
  Q_OBJECT
private:
  static const int repeatCount = 1000;
  QWidget* _testWidget;
  QLabel* _lblFps;
  QPushButton* _btnSwitch;
  bool _isGl;
  int _frameCount;
  QTime _start;

protected:
  void timerEvent(QTimerEvent* e);

public:
  MainWindow();

public slots:
  void switchWidget();
  void paintSquare(QPainter* p);
};

#endif
