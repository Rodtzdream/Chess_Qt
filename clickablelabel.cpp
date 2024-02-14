#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {

}

ClickableLabel::~ClickableLabel() {
    this->clear();
}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    emit clicked();
}
