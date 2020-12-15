#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

class Point {
	int x_, y_;
public: 
	Point(int x, int y) : x_(x), y_(y) {}

	int get_x() const {
		return x_;
	}

	int get_y() const {
		return y_;
	}

	Point move_with(int x, int y) const {
		return Point(x_ + x, y_ + y);
	}
};

class HilbertCurve {
	std::vector<Point> curve_;

	static void concat(std::vector<Point>& target, const std::vector<Point>& source) {
		target.insert(target.end(), source.begin(), source.end());
	}

	std::vector<Point> up(Point start, int order, int line) {
		std::vector<Point> result;
		if (order == 0) {
			result.push_back(start);
			return result;
		}
		concat(result, left(start, order - 1, line));
		start = result.back().move_with(0, -line);
		concat(result, up(start, order - 1, line));
		start = result.back().move_with(line, 0);
		concat(result, up(start, order - 1, line));
		start = result.back().move_with(0, line);
		concat(result, right(start, order - 1, line));
		return result;
	}

	std::vector<Point> down(Point start, int order, int line) {
		std::vector<Point> result;
		if (order == 0) {
			result.push_back(start);
			return result;
		}
		concat(result, left(start, order - 1, line));
		start = result.back().move_with(0, line);
		concat(result, down(start, order - 1, line));
		start = result.back().move_with(-line, 0);
		concat(result, down(start, order - 1, line));
		start = result.back().move_with(0, -line);
		concat(result, right(start, order - 1, line));
		return result;
	}

	std::vector<Point> right(Point start, int order, int line) {
		std::vector<Point> result;
		if (order == 0) {
			result.push_back(start);
			return result;
		}
		concat(result, down(start, order - 1, line));
		start = result.back().move_with(-line, 0);
		concat(result, right(start, order - 1, line));
		start = result.back().move_with(0, line);
		concat(result, right(start, order - 1, line));
		start = result.back().move_with(line, 0);
		concat(result, up(start, order - 1, line));
		return result;
	}

	std::vector<Point> left(Point start, int order, int line) {
		std::vector<Point> result;
		if (order == 0) {
			result.push_back(start);
			return result;
		}
		concat(result, up(start, order - 1, line));
		start = result.back().move_with(line, 0);
		concat(result, left(start, order - 1, line));
		start = result.back().move_with(0, -line);
		concat(result, left(start, order - 1, line));
		start = result.back().move_with(-line, 0);
		concat(result, down(start, order - 1, line));
		return result;
	}
public:
	HilbertCurve(int order, int width) {
		curve_ = up(Point(0, width), order, width / count_lines(order));
	}

	static int count_lines(int order) {
		if (order == 1) {
			return 1;
		}
		return 2 * count_lines(order - 1) + 1;
	}

	void draw(std::ostream& out) {
		out << "newpath" << std::endl;
		out << curve_[0].get_x() << " " << curve_[0].get_y() << " moveto" << std::endl;
		for (int i = 1; i < curve_.size(); i++) {
			out << curve_[i].get_x() << " " << curve_[i].get_y() << " lineto" << std::endl;
		}
		out << "stroke" << std::endl;
	}
};

int main() {
	HilbertCurve hc(10, 10);
	std::ofstream file("hilbert.ps");
	hc.draw(file);
	file.close();
	return 0;
}
