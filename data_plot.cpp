#include <stdlib.h>
#include <qwt_painter.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_widget.h>
#include <qwt_legend.h>
#include <qwt_scale_draw.h>
#include <qwt_math.h>
#include "data_plot.h"
#include <qwt_symbol.h>
//#include <qwt_plot_grid.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>


//
//  Initialize main window
//
DataPlot::DataPlot(QWidget *parent):
    QwtPlot(parent)
{
    setCanvasBackground(QColor(Qt::white));
//     QwtPlotGrid *grid = new QwtPlotGrid;
//     grid->enableXMin(true);
//     grid->setMajPen(QPen(Qt::white, 0, Qt::DotLine));
//     grid->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));
//     grid->attach(this);
    // Disable polygon clipping
    QwtPainter::setDeviceClipping(false);

    // We don't need the cache here
    canvas()->setPaintAttribute(QwtPlotCanvas::PaintCached, false);
    canvas()->setPaintAttribute(QwtPlotCanvas::PaintPacked, false);

#if QT_VERSION >= 0x040000
#ifdef Q_WS_X11
    /*
       Qt::WA_PaintOnScreen is only supported for X11, but leads
       to substantial bugs with Qt 4.2.x/Windows
     */
    canvas()->setAttribute(Qt::WA_PaintOnScreen, true);
#endif
#endif

    alignScales();
    
    insertLegend(new QwtLegend(), QwtPlot::BottomLegend);

    QwtSymbol sym;
    sym.setStyle(QwtSymbol::Ellipse);
    sym.setPen(QColor(Qt::black));
    sym.setSize(5);
    // Insert new curves
    QwtPlotCurve *cRight = new QwtPlotCurve("data");
    cRight->setStyle(QwtPlotCurve::Lines);
    cRight->setSymbol(sym);
    cRight->attach(this);

    // Set curve styles
    cRight->setPen(QPen(Qt::blue));

    cRight->setRawData(d_x, d_y, PLOT_SIZE);


#if 0
    //  Insert zero line at y = 0
    QwtPlotMarker *mY = new QwtPlotMarker();
    mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setYValue(0.0);
    mY->attach(this);
#endif

    // Axis 
    setAxisTitle(QwtPlot::xBottom, "Time/microseconds(200ms/point)");
    //setAxisScale(QwtPlot::xBottom, 0, PLOT_SIZE-1,1);

    setAxisTitle(QwtPlot::yLeft, "Values");
    setAxisScale(QwtPlot::yLeft, 0, 10);

    QwtPlotMagnifier *zoomer = new QwtPlotMagnifier(canvas());
    zoomer->setAxisEnabled(QwtPlot::xBottom,true);
    zoomer->setAxisEnabled(QwtPlot::yLeft,false);

    QwtPlotPanner *panner =new QwtPlotPanner(canvas());
    panner->setMouseButton(Qt::LeftButton);
    panner->setAxisEnabled(QwtPlot::xBottom,true);
    panner->setAxisEnabled(QwtPlot::yLeft,false);

//    Zoomer *zoomer = new Zoomer(canvas());
//    zoomer->setRubberBandPen(QPen(Qt::red, 2, Qt::DotLine));
//    zoomer->setTrackerPen(QPen(Qt::red));;
   // setTimerInterval(200);
}
void DataPlot::setData(double x[PLOT_SIZE],double y[PLOT_SIZE])
{
    memcpy(d_x,x,PLOT_SIZE*sizeof(double));
    memcpy(d_y,y,PLOT_SIZE*sizeof(double));
    double max = d_y[0],min=d_y[0];
    for(int i= 0; i<PLOT_SIZE; i++)
    {
        if(min>d_y[i])
            min = d_y[i] ;
        if(max<d_y[i])
            max = d_y[i] ;
    }

    setAxisScale(QwtPlot::yLeft, min-1, max+1);

    replot();
}

//
//  Set a plain canvas frame and align the scales to it
//
void DataPlot::alignScales()
{
    // The code below shows how to align the scales to
    // the canvas frame, but is also a good example demonstrating
    // why the spreaded API needs polishing.

    canvas()->setFrameStyle(QFrame::Box | QFrame::Plain );
    canvas()->setLineWidth(1);

    //int a = QwtPlot::axisCnt;
    for ( int i = 0; i < QwtPlot::axisCnt; i++ )
    {
        QwtScaleWidget *scaleWidget = (QwtScaleWidget *)axisWidget(i);
        if ( scaleWidget )
            scaleWidget->setMargin(0);

        QwtScaleDraw *scaleDraw = (QwtScaleDraw *)axisScaleDraw(i);
        if ( scaleDraw )
            scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, false);
    }
}


