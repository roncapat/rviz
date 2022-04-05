/*
 * Copyright (c) 2012, Willow Garage, Inc.
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
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
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

#ifndef RVIZ_TRAV_PLUGINS__PANELS__MAP_PALETTE_PANEL_HPP_
#define RVIZ_TRAV_PLUGINS__PANELS__MAP_PALETTE_PANEL_HPP_

#include "rviz_common/panel.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rviz_default_plugins/visibility_control.hpp"

class QLineEdit;
class QComboBox;
class QCheckBox;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QWidget;

namespace rviz_common
{
  class VisualizationManager;
  class Display;
  class Panel;
  class Config;
}

namespace rviz_default_plugins
{
namespace panels
{

/**
 * \class MapPalettePanel
 *
 */
class RVIZ_DEFAULT_PLUGINS_PUBLIC MapPalettePanel : public rviz_common::Panel
{
  Q_OBJECT

public:
  explicit MapPalettePanel(QWidget * parent = nullptr);
  void setPalette(const std::vector<unsigned char> &palette);
  virtual void onInitialize();

protected Q_SLOTS:
  virtual void load(const rviz_common::Config & config);
  virtual void save(rviz_common::Config config) const;

protected:
  unsigned char count = 0;
  QVBoxLayout *layout;
  std::vector<QWidget*> tiles; 
  QVBoxLayout* pushValueLabel(const QString &label, int pixels);
  QVBoxLayout* pushRangeLabel(const QString &label, int dim, int pixels);
};

}  // namespace panels
}  // namespace rviz_trav_plugins

#endif  // RVIZ_TRAV_PLUGINS__PANELS__MAP_PALETTE_PANEL_HPP_
