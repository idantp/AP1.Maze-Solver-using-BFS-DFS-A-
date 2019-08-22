//
// Created by roy on 07/01/19.
//

#ifndef ROYANDIDANPROJECT2_POINT_H
#define ROYANDIDANPROJECT2_POINT_H


class Point {
private:
    int left;
    int right;
public:

    Point(int l, int r);
    int getRight() const;
    int getLeft() const;
    const bool operator==(const Point& second) const;

};


#endif //ROYANDIDANPROJECT2_POINT_H
