#include "custompainter.h"
#include <QBrush>
#include <QPainter>
#include <QSGNode>

CustomPainter::CustomPainter(QQuickItem *parent): QQuickPaintedItem(parent){
   brush = new QBrush(QColor("#007430"));
}

bool CustomPainter::checkSize(int currentWidth, int currentHeight) {
    if(oldHeight != currentHeight || oldWidth != currentWidth) {
        oldHeight = currentHeight;
        oldWidth = currentWidth;
        if(pixmap != nullptr)
            delete pixmap;
        pixmap = new QPixmap(oldWidth, oldHeight);
        if(pathPainter != nullptr)
            delete pathPainter;
        pathPainter = new QPainter(pixmap);
        return true;
    }
    return false;
}

void CustomPainter::paint(QPainter *painter)
{
    checkSize(width(), height());
    painter->setBrush(*brush);
    painter->setPen(Qt::NoPen);
    painter->drawRoundedRect(0, 0, width(), height(), 10, 10);
    if(pixmap != nullptr)
        pixmap->fill(Qt::transparent);
    for(PathData* pathData:paths) {
        if(pathData != nullptr && pathData->path != nullptr && pathData->pen != nullptr && pathPainter != nullptr){
            if(pathData->isClear){
               pathPainter->setCompositionMode(QPainter::CompositionMode_Clear);
            } else {
               pathPainter->setCompositionMode(QPainter::CompositionMode_Source);
            }
            pathPainter->strokePath(*pathData->path, *pathData->pen);
        }
    }
    if(pixmap != nullptr)
        painter->drawPixmap(0, 0, width(), height(), *pixmap);
}


void CustomPainter::onEnter(float mouseX, float mouseY) {
    currentPath = new QPainterPath();
    currentPath->moveTo(mouseX, mouseY);
    oldMouseX = mouseX;
    oldMouseY = mouseY;
    QPen* pen = new QPen();
    QBrush brush = QBrush();
    brush.setStyle(Qt::SolidPattern);
    pen->setBrush(QBrush());
    pen->setWidth(15);
    pen->setStyle(Qt::SolidLine);
    pen->setCapStyle(Qt::RoundCap);
    pen->setColor(QColor("#003074"));
    pen->setJoinStyle(Qt::RoundJoin);
    paths.push_back(new PathData(currentPath, pen, isClear));
}

void CustomPainter::onPositionChanged(float mouseX, float mouseY) {
    if(currentPath != nullptr){
        currentPath->quadTo(oldMouseX, oldMouseY, (oldMouseX + mouseX)/2, (oldMouseY + mouseY)/2);
        oldMouseX = mouseX;
        oldMouseY = mouseY;
        update();
    }
}

void CustomPainter::onReleased(float mouseX, float mouseY) {
    currentPath = nullptr;
}

void CustomPainter::onChangeClearState(){
    isClear = !isClear;
}
