/*
MIT License

Copyright (c) 2020 Paddington Software Services

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef PIECHART_H
#define PIECHART_H

#include "chart.h"
#include "axislabelsettings.h"
#include "mousedisplay.h"

#include <QBrush>
#include <QPen>
#include <QPointF>
#include <QString>
#include <QWidget>
#include <QWheelEvent>

#include <list>
#include <set>
#include <vector>
class QColor;
class QPaintEvent;

namespace PssCharts {

class PieChart : public Chart
{
    Q_OBJECT

    struct cmpGreaterKey {
        // comparison function for drawing the slices
        bool operator()(const double& a, const double& b) const {
            return a > b;
        }
    };

protected:
    std::map<std::string, double> m_mapPoints;
    std::multimap<double,std::string, cmpGreaterKey> m_mapData;
    std::pair<uint32_t, double> ConvertFromPlotPoint(const QPointF& point) override;
    QBrush m_brushLine;
    QBrush m_brushFill;
    bool m_fEnableFill; //! Does the chart get filled
    int m_size;
    bool m_fDountHole;
    int m_nDountSize;
    int m_nStartingAngle;
    double m_nTotal;
    double m_nRatio;

    QRect MouseOverTooltipRect(const QPainter& painter, const QRect& rectFull, const QPointF& pointCircleCenter, const QString& strLabel) const;
    void ProcessChangedData() override;

public:
    PieChart(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    QRect ChartArea() const;
    void AddDataPoint(const std::string& label, const double& value);
    void RemoveDataPoint(const std::string& label);
    void SetDataPoints(const std::map<std::string, double>& mapPoints);
    void SetFillBrush(const QBrush& brush);
    void EnableFill(bool fEnable);
    void SetLineBrush(const QBrush& brush);
    void SetLineWidth(int nWidth);
    void SetChartSize(int nSize);
    void SetStartingAngle(int nAngle);
    void SetDonutSize(int nSize);
    void EnableDonut(bool fEnable);
};

} //namespace
#endif // PIECHART_H