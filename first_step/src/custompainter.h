#ifndef CUSTOMPAINTER_H
#define CUSTOMPAINTER_H
#include <QQuickPaintedItem>
#include <QPainterPath>
#include <list>


class PathData{


public:
    PathData(QPainterPath* path, QPen* pen, bool isClear = false){
        this->path = path;
        this->pen = pen;
        this->isClear = isClear;
    }
    QPainterPath* path;
    QPen* pen;
    QPixmap* pixmap;
    bool isClear = false;
};

class CustomPainter: public QQuickPaintedItem {
Q_OBJECT
public:
    CustomPainter(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;
    bool isClear = false;
private:
    QBrush* brush;
    QBrush* pathBrush;
    QPainterPath* currentPath = nullptr;
    float oldMouseX = -1;
    float oldMouseY = -1;
    std::list<PathData *> paths;
    QPen* pathPen;
    int oldWidth = -1;
    int oldHeight = -1;
    QPixmap* pixmap = nullptr;
    QPainter* pathPainter;

    bool checkSize(int currentWidth, int currentHeight);

public slots:
    void onEnter(float mouseX, float mouseY);
    void onPositionChanged(float mouseX, float mouseY);
    void onReleased(float mouseX, float mouseY);
    void onChangeClearState();
};


#endif // CUSTOMPAINTER_H
