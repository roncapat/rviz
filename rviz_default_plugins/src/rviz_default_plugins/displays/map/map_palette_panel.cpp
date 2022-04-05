/*
 * Copyright (c) 2022, Patrick Roncagliolo
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Patrick Roncagliolo nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "rviz_default_plugins/displays/map/map_palette_panel.hpp"

#include <iostream>

#include <Qt>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QCheckBox>
#include <QSlider>
#include <QComboBox>
#include <QPalette>
#include <QColor>
#include <QFrame>

#include "rviz_common/visualization_manager.hpp"
#include "rviz_common/frame_manager_iface.hpp"
#include "rviz_common/display_group.hpp"

namespace rviz_default_plugins
{
namespace panels
{

MapPalettePanel::MapPalettePanel(QWidget * parent)
: rviz_common::Panel(parent)
{
  setFixedHeight(150);

  layout = new QVBoxLayout(this);
  layout->setSpacing(0);

  auto w1 = new QWidget(this);
  auto w2 = new QWidget(this);
  auto w3 = new QWidget(this);
  layout->addWidget(w1);
  layout->addWidget(w2);
  layout->addWidget(w3);
  w1->show();
  w2->show();
  w3->show();
  w1->setFixedHeight(48);
  w2->setFixedHeight(48);
  w3->setFixedHeight(48);
  w1->setContentsMargins(0, 0, 0, 0);
  w2->setContentsMargins(0, 0, 0, 0);
  w3->setContentsMargins(0, 0, 0, 0);

  auto h1 = new QHBoxLayout(w1);
  auto h2 = new QHBoxLayout(w2);
  auto h3 = new QHBoxLayout(w3);
  h1->setSpacing(0);
  h2->setSpacing(0);
  h3->setSpacing(0);

  auto vv_free = pushValueLabel("Free", 65);
  auto vv_legal = pushRangeLabel("Legal", 98, 400);
  auto vv_inscribed = pushValueLabel("Inflation", 65);
  auto vv_obstacle = pushValueLabel("Obstacle", 65);
  auto vv_illegal_p = pushRangeLabel("Illegal", 27, 200);
  auto vv_illegal_n = pushRangeLabel("Illegal", 127, 200);
  auto vv_unknown = pushValueLabel("Unknown", 65);

  h1->addStretch();
  h1->addLayout(vv_free);
  h1->addSpacing(30);
  h1->addLayout(vv_inscribed);
  h1->addSpacing(30);
  h1->addLayout(vv_obstacle);
  h1->addSpacing(30);
  h1->addLayout(vv_unknown);
  h1->addStretch();

  h2->addStretch();
  h2->addLayout(vv_legal);
  h2->addStretch();

  h3->addStretch();
  h3->addLayout(vv_illegal_n);
  h3->addSpacing(76);
  h3->addLayout(vv_illegal_p);
  h3->addStretch();

  layout->setContentsMargins(11, 5, 11, 5);
}

QVBoxLayout* MapPalettePanel::pushValueLabel(const QString &label, int pixels) {
  auto vv = new QVBoxLayout();
  auto f = new QFrame(this);
  f->setFrameShape(QFrame::Box);
  f->setLineWidth(1);
  auto hh = new QHBoxLayout(f);
  auto w = new QWidget(this);
  auto l = new QLabel(label);
  vv->addWidget(f);
  vv->addWidget(l);
  hh->setSpacing(0);
  hh->setContentsMargins(0, 0, 0, 0);
  hh->addWidget(w);
  w->setFixedSize({pixels-2, 10});
  w->setAutoFillBackground(true);
  w->show();
  vv->setAlignment(w, Qt::AlignHCenter);
  vv->setAlignment(l, Qt::AlignHCenter);
  f->setFixedSize({pixels, 12});
  tiles.push_back(w);
  ++count;
  vv->setSpacing(0);
  return vv;
}

QVBoxLayout* MapPalettePanel::pushRangeLabel(const QString &label, int dim, int pixels) {
  auto vv = new QVBoxLayout();
  auto f = new QFrame(this);
  f->setFrameShape(QFrame::Box);
  f->setLineWidth(1);
  auto hh = new QHBoxLayout(f);
  auto tt = new QHBoxLayout();
  vv->addWidget(f);
  vv->addLayout(tt);
  hh->setSpacing(0);
  hh->setContentsMargins(0, 0, 0, 0);
  hh->addStretch();
  for (int i = count; i < count+dim; i++) {
    auto w = new QWidget(this);
    hh->addWidget(w);
    w->setFixedSize({std::max(1, static_cast<int>(std::round(pixels/dim))), 10});
    w->setAutoFillBackground(true);
    w->show();
    tiles.push_back(w);
  }
  f->setFixedSize(std::max(1, static_cast<int>(std::round(pixels/dim)))*dim, 12);
  hh->addStretch();
  tt->addWidget(new QLabel(std::to_string((signed char)count).c_str()));
  tt->addStretch();
  tt->addWidget(new QLabel(label));
  tt->addStretch();
  tt->addWidget(new QLabel(std::to_string((signed char)count+dim-1).c_str()));
  count = count + dim;
  vv->setSpacing(0);
  return vv;
}

void MapPalettePanel::onInitialize()
{
}

void MapPalettePanel::setPalette(const std::vector<unsigned char> &p)
{
  for (int i = 0; i <= 255; i++) {
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(p[i*4], p[i*4+1], p[i*4+2], p[i*4+3]));
    tiles[i]->setPalette(pal);
    tiles[i]->show();
  }
}

void MapPalettePanel::load(const rviz_common::Config & config)
{
  rviz_common::Panel::load(config);
}

void MapPalettePanel::save(rviz_common::Config config) const
{
  rviz_common::Panel::save(config);
}

}  // namespace rviz_trav_plugins
} // namespace panels

//#include <pluginlib/class_list_macros.hpp>  // NOLINT
//PLUGINLIB_EXPORT_CLASS(rviz_trav_plugins::panels::MapPalettePanel, rviz_common::Panel)
