#include "geometry.hpp"

Vector::Vector() : x_(0), y_(0) {}
Vector::Vector(int64_t xxx, int64_t yyy) : x_(xxx), y_(yyy) {}
Vector::Vector(const Vector& copy) { *this = copy; }

Vector& Vector::operator=(const Vector& other) {
  x_ = other.x_;
  y_ = other.y_;
  return *this;
}

int64_t operator*(const Vector& etot, const Vector& other) {
  return (etot.x_ * other.x_ + etot.y_ * other.y_);
}

int64_t operator^(const Vector& etot, const Vector& other) {
  return (etot.x_ * other.y_ - etot.y_ * other.x_);
}

Vector Vector::operator+(const Vector& other) const {
  Vector ans = *this;
  ans += other;
  return ans;
}

Vector Vector::operator-(const Vector& other) const {
  Vector ans(x_ - other.x_, y_ - other.y_);
  return ans;
}

Vector& Vector::operator+=(const Vector& other) {
  x_ += other.x_;
  y_ += other.y_;
  return *this;
}

Vector& Vector::operator-=(const Vector& other) {
  Vector ans(x_ - other.x_, y_ - other.y_);
  *this = ans;
  return *this;
}

Vector Vector::operator*(int n) const {
  Vector ans = *this;
  ans *= n;
  return ans;
}

Vector& Vector::operator*=(int n) {
  Vector ans(x_ * n, y_ * n);
  *this = ans;
  return *this;
}

Vector operator*(int n, const Vector& vec) {
  Vector ans = vec * n;
  return ans;
}

Vector Vector::operator-() const {
  Vector ans = *this;
  ans.x_ = -ans.x_;
  ans.y_ = -ans.y_;
  return ans;
}

int64_t Vector::GetX() const { return x_; }
int64_t Vector::GetY() const { return y_; }
IShape::~IShape() {}

Point::Point() {
  xxx_ = 0;
  yyy_ = 0;
}

Point::Point(int64_t aaa, int64_t bbb) {
  xxx_ = aaa;
  yyy_ = bbb;
}

Point::Point(const Point& copy) { *this = copy; }

Point& Point::operator=(const Point& other) {
  xxx_ = other.xxx_;
  yyy_ = other.yyy_;
  return *this;
}

int64_t Point::GetX() const { return xxx_; }
int64_t Point::GetY() const { return yyy_; }

void Point::Move(const Vector& vec) {
  xxx_ += vec.GetX();
  yyy_ += vec.GetY();
}

bool Point::ContainsPoint(const Point& point) {
  Point point = *this;
  return ((point.xxx_ == point.xxx_) && (point.yyy_ == point.yyy_));
}

bool Point::CrossSegment(const Segment& segment) {
  Segment copy = segment;
  if (copy.GetA().GetX() == copy.GetB().GetX() &&
      copy.GetA().GetY() == copy.GetB().GetY()) {
    return copy.GetA().ContainsPoint(*this);
  }
  Point aaa = copy.GetA();
  Point bbb = copy.GetB();
  Point ccc = *this;
  if (((ccc - aaa) ^ (bbb - aaa)) == 0) {
    if (((ccc - aaa) * (bbb - aaa)) >= 0) {
      if (((ccc - bbb) * (aaa - bbb)) >= 0) {
        return true;
      }
    }
  }
  return false;
}

Segment::Segment(const Point& aaa, const Point& bbb) {
  aaa_ = aaa;
  bbb_ = bbb;
}

Segment::Segment(const Segment& copy) { *this = copy; }

Segment& Segment::operator=(const Segment& copy) {
  aaa_ = copy.aaa_;
  bbb_ = copy.bbb_;
  return *this;
}

Point Segment::GetA() const { return aaa_; }
Point Segment::GetB() const { return bbb_; }

void Segment::Move(const Vector& vec) {
  aaa_.Move(vec);
  bbb_.Move(vec);
}

Vector Point::operator-(const Point& bbb) {
  Point left = *this;
  Point right = bbb;
  Vector res(left.GetX() - right.GetX(), left.GetY() - right.GetY());
  return res;
}

bool Segment::ContainsPoint(const Point& point) {
  Point point = point;
  Segment copy = *this;
  if (copy.aaa_.GetX() == copy.bbb_.GetX() &&
      copy.aaa_.GetY() == copy.bbb_.GetY()) {
    aaa_.ContainsPoint(point);
  }
  if (((copy.bbb_ - copy.aaa_) ^ (point - copy.aaa_)) == 0) {
    if (point.GetX() <= std::max(copy.aaa_.GetX(), copy.bbb_.GetX()) &&
        point.GetX() >= std::min(copy.aaa_.GetX(), copy.bbb_.GetX())) {
      if (point.GetY() >= std::min(copy.aaa_.GetY(), copy.bbb_.GetY()) &&
          point.GetY() <= std::max(copy.aaa_.GetY(), copy.bbb_.GetY())) {
        return true;
      }
    }
  }
  return false;
}

bool Segment::CrossSegment(const Segment& segment) {
  Vector abb = (bbb_ - aaa_);
  Segment other = segment;
  Vector cdd = (other.GetB() - other.GetA());
  Vector acc = (other.GetA() - aaa_);
  Vector add = (other.GetB() - aaa_);
  Vector caa = (aaa_ - other.GetA());
  Vector cbb = (bbb_ - other.GetA());
  if (((abb ^ acc) * (abb ^ add) == 0) && ((cdd ^ caa) * (cdd ^ cbb) == 0)) {
    return (other.ContainsPoint(aaa_) || other.ContainsPoint(bbb_) ||
            ContainsPoint(other.aaa_) || ContainsPoint(other.bbb_));
  }
  return (((abb ^ acc) * (abb ^ add) <= 0) && ((cdd ^ caa) * (cdd ^ cbb) <= 0));
}

Line::Line(const Point& pt1, const Point& pt2) {
  pt1_ = pt1;
  pt2_ = pt2;
  aa_ = pt2.GetY() - pt1.GetY();
  bb_ = pt1.GetX() - pt2.GetX();
  cc_ = (pt2.GetX() * pt1.GetY()) - (pt2.GetY() * pt1.GetX());
}

Line::Line(const Line& other) { *this = other; }

Line& Line::operator=(const Line& other) {
  pt1_ = other.pt1_;
  pt2_ = other.pt2_;
  aa_ = other.aa_;
  bb_ = other.bb_;
  cc_ = other.cc_;
  return *this;
}

int64_t Line::GetA() const { return aa_; }
int64_t Line::GetB() const { return bb_; }
int64_t Line::GetC() const { return cc_; }

void Line::Move(const Vector& vec) {
  pt1_.Move(vec);
  pt2_.Move(vec);
  aa_ = pt2_.GetY() - pt1_.GetY();
  bb_ = pt1_.GetX() - pt2_.GetX();
  cc_ = (pt2_.GetX() * pt1_.GetY()) - (pt2_.GetY() * pt1_.GetX());
}

bool Line::ContainsPoint(const Point& point) {
  Point copy = point;
  Vector line(pt2_.GetX() - pt1_.GetX(), pt2_.GetY() - pt1_.GetY());
  Vector pline(pt2_.GetX() - copy.GetX(), pt2_.GetY() - copy.GetY());
  return ((line ^ pline) == 0);
}

bool Line::CrossSegment(const Segment& segment) {
  Segment copy = segment;
  Line line = *this;
  Point aaa = copy.GetA();
  Point bbb = copy.GetB();
  Line seg(aaa, bbb);
  Vector lin(line.GetA(), line.GetB());
  Vector segm(seg.GetA(), seg.GetB());
  if (copy.GetA().GetX() == copy.GetB().GetX() &&
      copy.GetA().GetY() == copy.GetB().GetY()) {
    line.ContainsPoint(copy.GetA());
  }
  if ((lin ^ segm) == 0) {
    return true;
  }
  int64_t lpoint = line.GetA() * copy.GetA().GetX() +
                   line.GetB() * copy.GetA().GetY() + line.GetC();
  int64_t rpoint = line.GetA() * copy.GetB().GetX() +
                   line.GetB() * copy.GetB().GetY() + line.GetC();
  return (std::min(lpoint, rpoint) <= 0 && std::max(lpoint, rpoint) >= 0);
}

Ray::Ray(const Point& left, const Point& right) {
  begin_ = left;
  Point lll = left;
  Point rrr = right;
  direction_ = rrr - lll;
}

Ray& Ray::operator=(const Ray& other) {
  begin_ = other.begin_;
  direction_ = other.direction_;
  return *this;
}

Ray::Ray(const Ray& other) { *this = other; }
Point Ray::GetA() { return begin_; }
Vector Ray::GetVector() { return direction_; }
void Ray::Move(const Vector& vec) { begin_.Move(vec); }

bool Ray::ContainsPoint(const Point& point) {
  Point copy = point;
  Vector pvec = copy - begin_;
  if ((pvec ^ direction_) == 0) {
    if ((pvec * direction_) >= 0) {
      return true;
    }
  }
  return false;
}

bool Ray::CrossSegment(const Segment& segment) {
  Segment copy = segment;
  Vector acentr = copy.GetA() - begin_;
  Vector bcentr = copy.GetB() - begin_;
  if ((acentr ^ direction_) == 0 || (bcentr ^ direction_) == 0) {
    return (ContainsPoint(copy.GetA()) || ContainsPoint(copy.GetB()));
  }
  return ((acentr * direction_) >= 0 && (bcentr * direction_) >= 0);
}

Circle::Circle(const Point& point, size_t radius) {
  centre_ = point;
  rad_ = radius;
}

Circle& Circle::operator=(const Circle& other) {
  centre_ = other.centre_;
  rad_ = other.rad_;
  return *this;
}

Circle::Circle(const Circle& other) { *this = other; }
Point Circle::GetCentre() const { return centre_; }
size_t Circle::GetRadius() const { return rad_; }
void Circle::Move(const Vector& vec) { centre_.Move(vec); }

bool Circle::ContainsPoint(const Point& point) {
  return (centre_.Dlina(point) <= (int64_t)rad_ * (int64_t)rad_);
}

int64_t Point::Dlina(const Point& other) {
  Point copy = *this;
  int64_t ans = ((copy.GetX() - other.xxx_) * (copy.GetX() - other.xxx_) +
                 (copy.GetY() - other.yyy_) * (copy.GetY() - other.yyy_));
  return ans;
}

bool Circle::CrossSegment(const Segment& segment) {
  Segment copy = segment;
  Circle circle = *this;
  if (copy.GetA().GetX() == copy.GetB().GetX() &&
      copy.GetA().GetY() == copy.GetB().GetY()) {
    return circle.ContainsPoint(copy.GetA());
  }
  if (circle.centre_.Dlina(copy.GetA()) <
          ((int64_t)circle.rad_ * (int64_t)circle.rad_) &&
      circle.centre_.Dlina(copy.GetB()) <
          ((int64_t)circle.rad_ * (int64_t)circle.rad_)) {
    return false;
  }
  if (circle.centre_.Dlina(copy.GetA()) ==
          ((int64_t)circle.rad_ * (int64_t)circle.rad_) ||
      circle.centre_.Dlina(copy.GetB()) ==
          ((int64_t)circle.rad_ * (int64_t)circle.rad_)) {
    return true;
  }
  if ((circle.centre_.Dlina(copy.GetA()) <
           ((int64_t)circle.rad_ * (int64_t)circle.rad_) &&
       circle.centre_.Dlina(copy.GetB()) >
           ((int64_t)circle.rad_ * (int64_t)circle.rad_)) ||
      (circle.centre_.Dlina(copy.GetA()) >
           ((int64_t)circle.rad_ * (int64_t)circle.rad_) &&
       circle.centre_.Dlina(copy.GetB()) <
           ((int64_t)circle.rad_ * (int64_t)circle.rad_))) {
    return true;
  }
  Vector seg = copy.GetB() - copy.GetA();
  Vector rad = centre_ - copy.GetA();
  int64_t len = ((seg ^ rad) * (seg ^ rad)) /
                (seg.GetX() * seg.GetX() + seg.GetY() * seg.GetY());
  return (len <= (int64_t)circle.rad_ * (int64_t)circle.rad_);
}

IShape* Point::Clone() { return new Point(*this); }
IShape* Line::Clone() { return new Line(*this); }
IShape* Segment::Clone() { return new Segment(*this); }
IShape* Ray::Clone() { return new Ray(*this); }
IShape* Circle::Clone() { return new Circle(*this); }
