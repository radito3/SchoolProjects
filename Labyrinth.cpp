#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <random>

enum Direction {
    UP = 1,		// 00001
    LEFT = 1 << 1,	// 00010
    DOWN = 1 << 2,	// 00100
    RIGHT = 1 << 3	// 01000
};
// 01011 = UP | LEFT | RIGHT

class Cell {
    friend class Board;

    unsigned row_;
    unsigned col_;
    unsigned walls_;
    const static int SIZE = 5;
    bool visited_;

    static const char* draw_wall(bool has_wall) {
        return has_wall ? "rlineto" : "rmoveto";
    }

    void draw(std::ostream& out) const {
        out << SIZE * col() << " " << SIZE * row() << " moveto" << std::endl;
        out << SIZE << " " << 0 << " " << draw_wall(has_wall(DOWN)) << std::endl;
        out << 0 << " " << SIZE << " " << draw_wall(has_wall(RIGHT)) << std::endl;
        out << -SIZE << " " << 0 << " " << draw_wall(has_wall(UP)) << std::endl;
        out << 0 << " " << -SIZE << " " << draw_wall(has_wall(LEFT)) << std::endl;
    }

public:
    Cell(unsigned r, unsigned c, unsigned walls = UP|LEFT|DOWN|RIGHT)
            : row_(r), col_(c), walls_(walls), visited_(false) {}

    unsigned row() const {
        return row_;
    }

    unsigned col() const {
        return col_;
    }

    bool has_wall(Direction dir) const {
        return walls_ & dir;
    }

    Cell& set_wall(Direction dir) {
        walls_ |= dir;
        return *this;
    }

    Cell& unset_wall(Direction dir) {
        walls_ &= ~dir;
        return *this;
    }

    bool visited() const {
        return visited_;
    }

    Cell& mark_visited() {
        visited_ = true;
        return *this;
    }
};

class Board {
    unsigned height_;
    unsigned width_;
    std::vector<Cell> cells_;

    unsigned index(unsigned row, unsigned col) const {
        if (row >= width_ || col >= height_) {
            throw std::out_of_range("invalid index");
        }
        return row * width_ + col;
    }

    unsigned nindex(unsigned row, unsigned col, Direction dir) const {
        if (row >= height_ || col >= width_) {
            throw std::out_of_range("invalid index");
        }
        unsigned nrow = dir == UP ? row + 1 : (dir == DOWN ? row - 1 : row);
        unsigned ncol = dir == RIGHT ? col + 1 : (dir == LEFT ? col - 1 : col);
        if (nrow < 0 || nrow >= height_ || ncol < 0 || ncol >= width_) {
            throw std::out_of_range("invalid index");
        }
        return index(nrow, ncol);
    }

public:
    Board(unsigned w, unsigned h) : width_(w), height_(h) {
        for (unsigned row = 0; row < height_; row++) {
            for (unsigned col = 0; col < width_; col++) {
                cells_.emplace_back(row, col);
            }
        }
    }

    Cell& at(unsigned row, unsigned col) {
        return cells_[index(row, col)];
    }

    const Cell& at(unsigned row, unsigned col) const {
        return cells_[index(row, col)];
    }

    Cell& neighbour(const Cell& cell, Direction dir) {
        return cells_[nindex(cell.row(), cell.col(), dir)];
    }

    const Cell& neighbour(const Cell& cell, Direction dir) const {
        return cells_[nindex(cell.row(), cell.col(), dir)];
    }

    Cell& drill(Cell& cell, Direction dir) {
        Cell& ncell = neighbour(cell, dir);
        cell.unset_wall(dir);
        Direction opposite = opposite_direction(dir);
        ncell.unset_wall(opposite);
        return ncell;
    }

    static Direction opposite_direction(Direction dir) {
        switch (dir) {
            case UP:
                return DOWN;
            case LEFT:
                return RIGHT;
            case DOWN:
                return UP;
            case RIGHT:
                return LEFT;
            default:
                throw std::runtime_error("invalid direction");
        }
    }

    void draw(std::ostream& out) const {
        out << "newpath" << std::endl;
        for (int row = 0; row < height_; ++row) {
            for (int col = 0; col < width_; ++col) {
                at(row, col).draw(out);
            }
        }
        out << "1 setlinewidth" << std::endl;
        out << "stroke" << std::endl;
    }

private:
    const static Direction DIRECTIONS[];

public:
    bool has_neighbour(const Cell& cell, Direction dir) const {
        unsigned nrow = dir == UP ? cell.row() + 1 : (dir == DOWN ? cell.row() - 1 : cell.row());
        unsigned ncol = dir == RIGHT ? cell.col() + 1 : (dir == LEFT ? cell.col() - 1 : cell.col());
        if (ncol >= 0 && ncol < width_ && nrow >= 0 && nrow < height_) {
            return true;
        }
        return false;
    }

    bool has_unvisted_neighbour(const Cell& cell) const {
        for (int i = 0; i < 4; ++i) {
            Direction dir = DIRECTIONS[i];
            if (has_neighbour(cell, dir)) {
                const Cell& ncell = neighbour(cell, dir);
                if (!ncell.visited()) {
                    return true;
                }
            }
        }
        return false;
    }

    Direction get_random_unvisted_direction(const Cell& cell) const {
        if (!has_unvisted_neighbour(cell)) {
            throw std::runtime_error("cell has no unvisited neighbours");
        }
        while (true) {
            unsigned long dindex = std::mt19937(std::random_device()())() % 4;
            Direction dir = DIRECTIONS[dindex];
            if (has_neighbour(cell, dir)) {
                const Cell& ncell = neighbour(cell, dir);
                if (!ncell.visited()) {
                    return dir;
                }
            }
        }
    }

    void generate_maze(Cell& cell) {
        cell.mark_visited();
        while (true) {
            if (!has_unvisted_neighbour(cell)) {
                return;
            }
            Direction dir = get_random_unvisted_direction(cell);
            Cell& ncell = drill(cell, dir);
            generate_maze(ncell);
        }
    }
};

const Direction Board::DIRECTIONS[] = { UP, DOWN, LEFT, RIGHT };

int main() {
    Board b(10, 10);
    b.generate_maze(b.at(0, 0));
    std::ofstream file("lab.ps");
    b.draw(file);
    file.close();
    //std::cout << '(' << std::setfill('*') << std::setw(3) << "aa" << ')' << '(' << "bb" << ')';
    return 0;
}
