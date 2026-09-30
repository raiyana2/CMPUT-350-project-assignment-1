#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <cmath>
#include <iostream>

namespace CMPUT350 {

struct Point2D {
    float x, y;
    Point2D(float x = 0, float y = 0) : x(x), y(y) {}
    double Distance(const Point2D& other) const {
        //(DONE) TODO: write this code
        float dx = other.x - x;
        float dy = other.y - y;
        return std::sqrt(dx * dx + dy * dy);
    }
    Point2D operator+(const Point2D& other) const {
        //(DONE) TODO: write this code
        return Point2D(x + other.x, y + other.y);
    }
    Point2D operator+(const float& other) const {
        //(DONE) TODO: write this code
        return Point2D(x + other, y + other);  // here other is a single float
    }
    Point2D operator-(const Point2D& other) const {
        //(DONE) TODO: write this code
        return Point2D(x - other.x, y - other.y);
    }
    Point2D operator-(const float& other) const {
        //(DONE) TODO: write this code
        return Point2D(x - other, y - other);
    }
    Point2D operator*(const float& scalar) const {
        //(DONE) TODO: write this code
        return Point2D(x * scalar, y * scalar);
    }
    Point2D& operator+=(
        const float& scalar) {  // Point2D& means the function returns the same existing Point2D
                                // object, not a copy. so x = x + scalar, y = y + scalar, and then
                                // return the same object.
        // (DONE) TODO: write this code
        x += scalar;
        y += scalar;
        return *this;
    }
    Point2D& operator+=(const Point2D& other) {
        // (DONE) TODO: write this code
        x += other.x;
        y += other.y;
        return *this;
    }
    Point2D& operator-=(const Point2D& other) {
        // (DONE) TODO: write this code
        x -= other.x;
        y -= other.y;
        return *this;
    }
    bool operator==(const Point2D& other) const {
        // (DONE) TODO: write this code
        return (x == other.x && y == other.y);
    }
    Point2D& operator*=(const int& scalar) {
        // (DONE) TODO: write this code
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Point2D& operator/=(const int& scalar) {
        // (DONE) TODO: write this code
        x /= scalar;
        y /= scalar;
        return *this;
    }
    float operator*(
        const Point2D& other) const {  // dot product of two vectors, returns a scalar value`
        // (DONE) TODO: write this code
        return x * other.x + y * other.y;
    }
    float Dot(Point2D b) const {
        // (DONE) TODO: write this code
        return x * b.x + y * b.y;
    }
    static float Dot(Point2D a, Point2D b) {
        // (DONE) TODO: write this code
        return a.x * b.x + a.y * b.y;
    }
    static float Cross(Point2D a, Point2D b) {
        // (DONE) TODO: write this code
        return a.x * b.y - a.y * b.x;
    }
    void Normalize() {
        // (DONE) TODO: write this code
        float length = std::sqrt(x * x + y * y);
        if (length != 0) {
            x /= length;
            y /= length;
        }
    }
};

static std::ostream& operator<<(std::ostream& os, const Point2D& p) {
    // (DONE) TODO: write this code
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

static Point2D operator*(float number, const Point2D& rhs) {
    // (DONE) TODO: write this code
    return Point2D(number * rhs.x, number * rhs.y);
}

struct Line {
    Point2D p1, p2;

    Line(Point2D p1 = {0, 0}, Point2D p2 = {0, 0}) : p1(p1), p2(p2) {}
    Line(float x1, float y1, float x2, float y2) : p1(x1, y1), p2(x2, y2) {}
    float Length() const {
        // (DONE) TODO: write this code
        return p1.Distance(p2);
    }
    Point2D ClosestPoint(const Point2D& p) const {
        // (DONE) TODO: write this code
        Point2D direction = p2 - p1;
        float lengthSquared = direction * direction;  // dot product of direction with itself

        // p1 and p2 are the same point, so return p1
        if (lengthSquared == 0) {
            return p1;
        }
        float t = ((p - p1) * direction) /
                  lengthSquared;  // dot product of (p - p1) and direction, divided by lengthSquared

        // Closest point would be before p1
        if (t < 0) {
            return p1;
        }
        // Closest point would be after p2
        if (t > 1) {
            return p2;
        }

        return p1 + direction * t;  // Closest point is on the line segment
    }

    bool Crosses(Line other, Point2D& crossingPoint) const {
        // (DONE) TODO: write this code
        Point2D r = p2 - p1;
        Point2D s = other.p2 - other.p1;

        float denominator = Point2D::Cross(r, s);

        if (denominator == 0) {
            // Lines are parallel
            return false;
        }

        Point2D diff = other.p1 - p1;

        float t = Point2D::Cross(diff, s) / denominator;
        float u = Point2D::Cross(diff, r) / denominator;

        if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
            crossingPoint = p1 + r * t;
            return true;
        }

        return false;
    }
};

static std::ostream& operator<<(std::ostream& os, const Line& l) {
    // TODO: write this code
    os << "Line(" << l.p1 << ", " << l.p2 << ")";
    return os;
}

struct Circle {
    Point2D center;
    float radius;

    Circle(Point2D c = {0, 0}, float r = 0) : center(c), radius(r) {}

    Circle(float x, float y, float r) : center(x, y), radius(r) {}
};

struct Rect {
    Point2D topLeft;
    float width, height;

    Rect(float left, float top, float width, float height)
        : topLeft(Point2D(left, top)), width(width), height(height) {}

    Rect(Point2D tl = {0, 0}, int w = 0, int h = 0) : topLeft(tl), width(w), height(h) {}

    // Creates bounding box around p1 and p2 with positive width/height
    Rect(Point2D p1, Point2D p2)
        : topLeft(std::min(p1.x, p2.x), std::min(p1.y, p2.y)),
          width(fabs(p1.x - p2.x)),
          height(fabs(p1.y - p2.y)) {}

    Rect(Point2D center, float radius)
        : topLeft(center.x - radius, center.y - radius), width(2 * radius), height(2 * radius) {}

    Rect& operator|=(const Rect& other) {
        //(Done) TODO: write this code
        float left = std::min(topLeft.x, other.topLeft.x);
        float top = std::min(topLeft.y, other.topLeft.y);

        float right = std::max(topLeft.x + width, other.topLeft.x + other.width);
        float bottom = std::max(topLeft.y + height, other.topLeft.y + other.height);

        topLeft = Point2D(left, top);
        width = right - left;
        height = bottom - top;

        return *this;
    }
    Rect& operator|=(const Point2D& other) {
        //(Done) TODO: write this code
        float left = std::min(topLeft.x, other.x);
        float top = std::min(topLeft.y, other.y);
        float right = std::max(topLeft.x + width, other.x);
        float bottom = std::max(topLeft.y + height, other.y);

        topLeft = Point2D(left, top);
        width = right - left;
        height = bottom - top;

        return *this;
    }
    Rect& operator|=(const Line& other) {
        //(Done) TODO: write this code
        *this |= other.p1;
        *this |= other.p2;

        return *this;
    }
    Rect& operator&=(const Rect& other) {
        //(Done) TODO: write this code
        float left = std::max(topLeft.x, other.topLeft.x);
        float top = std::max(topLeft.y, other.topLeft.y);

        float right = std::min(topLeft.x + width, other.topLeft.x + other.width);
        float bottom = std::min(topLeft.y + height, other.topLeft.y + other.height);

        if (right < left || bottom < top) {
            // No intersection, set to empty rectangle
            topLeft = Point2D(0, 0);
            width = 0;
            height = 0;
        } else {
            topLeft = Point2D(left, top);
            width = right - left;
            height = bottom - top;
        }
        return *this;
    }
    Rect& operator+=(const Point2D& other) {
        //(Done) TODO: write this code
        topLeft += other;
        return *this;
    }
    Rect operator+(const Point2D& other) const {
        //(Done) TODO: write this code
        Rect result = *this;
        result += other;
        return result;
    }
    void Inset(int inset) {
        //(Done) TODO: write this code
        topLeft.x += inset;
        topLeft.y += inset;

        width -= 2 * inset;
        height -= 2 * inset;
    }
    bool IsInside(const Point2D& p) const {
        //(Done) TODO: write this code
        return p.x >= topLeft.x && p.x < topLeft.x + width && p.y >= topLeft.y &&
               p.y < topLeft.y + height;
    }

    bool overlaps(const Rect& other) const {
        bool notOverlap =
            topLeft.x > other.topLeft.x + other.width || topLeft.x + width < other.topLeft.x ||
            topLeft.y > other.topLeft.y + other.height || topLeft.y + height < other.topLeft.y;
        return !notOverlap;
    }
};

static std::ostream& operator<<(std::ostream& os, const Rect& l) {
    // (Done)TODO: write this code
    os << "Rect(" << l.topLeft << ", " << l.width << ", " << l.height << ")";
    return os;
}

}  // namespace CMPUT350

#endif  // MATHUTIL_H
