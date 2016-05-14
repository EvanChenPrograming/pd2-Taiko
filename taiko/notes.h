#ifndef NOTES_H
#define NOTES_H

#include <QGraphicsPixmapItem>

class notes : public QGraphicsPixmapItem
{
public:
    notes(int x);
    int symbol;
};

#endif // NOTES_H
