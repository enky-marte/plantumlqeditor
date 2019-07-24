/*
 * This file is part of PlantUML QEditor.
 *
 * PlantUML QEditor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PlantUML QEditor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PlantUML QEditor. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QWidget>
#include <QImage>

class QSvgRenderer;

class PreviewWidget : public QWidget
{
    Q_OBJECT
public:
    enum Mode { NoMode, PngMode, SvgMode };

    explicit PreviewWidget(QWidget *parent = nullptr);

    Mode mode() const { return m_mode; }
    void setMode(Mode new_mode) { m_mode = new_mode; }

    void load(const QByteArray &data, bool reset_zoom_factor = true);

    void wheelEvent(QWheelEvent* event);

public slots:
    void zoomOriginal() { setZoomScale(ZOOM_ORIGINAL_SCALE); }
    void zoomIn();
    void zoomOut();

private:
    static const int ZOOM_ORIGINAL_SCALE = 100;

    void paintEvent(QPaintEvent *);
    void zoomImage();
    void setZoomScale(int new_scale);

    QImage m_image;
    QImage m_zoomedImage;
    Mode m_mode;
    QSvgRenderer *m_svgRenderer;
    int m_zoomScale;
};

#endif // PREVIEWWIDGET_H
