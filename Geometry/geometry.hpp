#include <iostream>

class Vector {
public:
	Vector();
	Vector(int64_t xxx, int64_t yyy);
	Vector(const Vector& copy);
	~Vector() = default;
	Vector& operator=(const Vector& other);
	friend int64_t operator*(const Vector& etot, const Vector& other);
	friend int64_t operator^(const Vector& etot, const Vector& other);
	Vector operator+(const Vector& other) const;
	Vector operator-(const Vector& other) const;
	Vector& operator+=(const Vector& other);
	Vector& operator-=(const Vector& other);
	Vector operator*(int n) const;
	Vector& operator*=(int n);
	friend Vector operator*(int n, const Vector& vec);
	Vector operator-() const;
	int64_t GetX() const;
	int64_t GetY() const;

private:
	int64_t x_;
	int64_t y_;
};

class Point;
class Segment;
class Line;
class Ray;
class Circle;
class IShape {
public:
	virtual ~IShape() = 0;
	virtual void Move(const Vector& vec) = 0;
	virtual bool ContainsPoint(const Point& point) = 0;
	virtual bool CrossSegment(const Segment& segment) = 0;
	virtual IShape* Clone() = 0;
};
class Point : public IShape {
public:
	Point();
	Point(int64_t aaa, int64_t bbb);
	Point(const Point& copy);
	Point& operator=(const Point& other);
	~Point() = default;
	int64_t GetX() const;
	int64_t GetY() const;
	void Move(const Vector& vec) override;
	bool ContainsPoint(const Point& point) override;
	bool CrossSegment(const Segment& segment) override;
	IShape* Clone() override;
	Vector operator-(const Point& bbb);
	int64_t Dlina(const Point& other);

private:
	int64_t xxx_;
	int64_t yyy_;
};
class Segment : public IShape {
public:
	Segment() = default;
	Segment(const Point& aaa, const Point& bbb);
	Segment(const Segment& copy);
	Segment& operator=(const Segment& copy);
	~Segment() = default;
	Point GetA() const;
	Point GetB() const;
	void Move(const Vector& vec) override;
	bool ContainsPoint(const Point& point) override;
	bool CrossSegment(const Segment& segment) override;
	IShape* Clone() override;

private:
	Point aaa_;
	Point bbb_;
};
class Line : public IShape {
public:
	Line() = default;
	Line(const Point& pt1, const Point& pt2);
	Line(const Line& other);
	Line& operator=(const Line& other);
	~Line() = default;
	int64_t GetA() const;
	int64_t GetB() const;
	int64_t GetC() const;
	void Move(const Vector& vec) override;
	bool ContainsPoint(const Point& point) override;
	bool CrossSegment(const Segment& segment) override;
	IShape* Clone() override;

private:
	Point pt1_;
	Point pt2_;
	int64_t aa_, bb_, cc_;
};
class Ray : public IShape {
public:
	Ray() = default;
	Ray(const Point& left, const Point& right);
	Ray(const Ray& other);
	Ray& operator=(const Ray& other);
	~Ray() = default;
	Point GetA();
	Vector GetVector();
	void Move(const Vector& vec) override;
	bool ContainsPoint(const Point& point) override;
	bool CrossSegment(const Segment& segment) override;
	IShape* Clone() override;

private:
	Vector direction_;
	Point begin_;
};
class Circle : public IShape {
public:
	Circle() = default;
	Circle(const Point& point, size_t radius);
	Circle(const Circle& other);
	Circle& operator=(const Circle& other);
	~Circle() = default;
	Point GetCentre() const;
	size_t GetRadius() const;
	void Move(const Vector& vec) override;
	bool ContainsPoint(const Point& point) override;
	bool CrossSegment(const Segment& segment) override;
	IShape* Clone() override;

private:
	Point centre_;
	size_t rad_;
};
