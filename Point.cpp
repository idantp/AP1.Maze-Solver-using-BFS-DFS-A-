//
// Created by roy on 07/01/19.
//

#include "Point.h"


int Point::getLeft() const {
    return left;
}

int Point::getRight() const {
    return right;
}
//overloading operator == to check equality between two points.
const bool Point::operator==(const Point &second) const {
    return this->left == second.getLeft() && this->right == second.getRight();
}

//constructor.
Point::Point(int l, int r) {
    this->left = l;
    this->right = r;
}
