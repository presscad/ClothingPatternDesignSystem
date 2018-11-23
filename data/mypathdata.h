#ifndef MYPATHDATA_H
#define MYPATHDATA_H

#include <QPointF>
#include <QString>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QMap>
#include "curvepoint.h"

struct PathData{
    int id;
    bool isLine;
    int startPoint; //起点在pointData数组中的id
    int endPoint; //终点在pointData数组中的id
};

struct PointData{
    int id;
    CurvePoint *point;
};

class MyPathData
{
public:
    MyPathData(QString name);
    ~MyPathData();

    QString name="";
    QFile file;

    const static int MAX_NUM_POINT=500;
    const static int MAX_NUM_PATH=250;
    int numberPath=0;
    int numberPoint=0;
    PathData pathData[MAX_NUM_PATH];
    PointData pointData[MAX_NUM_POINT];
    QMap<QString,int> pointMap; //记录点的名称与id，用于查找特殊点，如smallCroPoint

    void addLineTo(QPointF endPoint);
    void addLine(QPointF startPoint,QPointF endPoint);

    void addCurve(QList<QPointF> points);
    void addCurve(QList<QPointF> points,QPointF ctrlPoint1,QPointF ctrlPoint2);

    void addPoint(QPointF point,QString name="");
    QPointF findPoint(QString name);

    bool saveTo(QString path);

private:
    const qreal E=0.1;

    bool equal(CurvePoint *p1,CurvePoint *p2); //判断两点是否相等（对应坐标相差不超过(E)mm）
    bool equal(CurvePoint p1,CurvePoint p2);
};

#endif // MYPATHDATA_H