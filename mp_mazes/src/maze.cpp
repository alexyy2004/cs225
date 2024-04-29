/* Your code here! */
#include "maze.h"
#include <queue>
#include <iostream>
#include <algorithm>
#include <map>

SquareMaze::SquareMaze() {
    set_ = new DisjointSets();
    width_ = 0;
    height_ = 0;
}

SquareMaze::~SquareMaze() {
    delete set_;
    set_ = nullptr;
}

bool SquareMaze::allConnected() {
    if (set_->size(0) != (height_ * width_)) {
        return false;
    }
    return true;
}

void SquareMaze::makeMaze(int width, int height) {
    width_ = width;
    height_ = height;
    int size = width_ * height_;
    set_->addelements(size);
    for (int i = 0; i < width_; i++) {
        std::vector<std::pair<bool, bool>> temp;
        for (int j = 0; j < height_; j++) {
            std::pair<bool, bool> p(true, true);
            temp.push_back(p);
        }
        maze_.push_back(temp);
    }

    while (!allConnected()) {
        int random_x = std::rand() % width_;
        int random_y = std::rand() % height_;
        int random_dir = std::rand() % 4;
        int elem = random_y * width_ + random_x;
        if (random_dir == 0) {
            if (random_x + 1 < width_) {
                if (set_->find(elem) != set_->find(elem + 1)) {
                    maze_[random_x][random_y].first = false;
                    set_->setunion(elem, elem + 1);
                }
            }
        }
        if (random_dir == 1) {
            if (random_y + 1 < height_) {
                if (set_->find(elem) != set_->find(elem + width_)) {
                    maze_[random_x][random_y].second = false;
                    set_->setunion(elem, elem + width_);
                }
            }
        }
        if (random_dir == 2) {
            if (random_x - 1 >= 0) {
                if (set_->find(elem) != set_->find(elem - 1)) {
                    maze_[random_x - 1][random_y].first = false;
                    set_->setunion(elem, elem - 1);
                }
            }
        }
        if (random_dir == 3) {
            if (random_y - 1 >= 0) {
                if (set_->find(elem) != set_->find(elem - width_)) {
                    maze_[random_x][random_y - 1].second = false;
                    set_->setunion(elem, elem - width_);
                }
            }
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    int elem = y * width_ + x;
    if (dir == 0) {
        if (x + 1 >= width_ || maze_[x][y].first == true) {
            return false;
        } else {
            return true;
        }
    }
    if (dir == 1) {
        if (y + 1 >= height_ || maze_[x][y].second == true) {
            return false;
        } else {
            return true;
        }
    }
    if (dir == 2) {
        if (x - 1 < 0 || maze_[x - 1][y].first == true) {
            return false;
        } else {
            return true;
        }
    }
    if (dir == 3) {
        if (y - 1 < 0 || maze_[x][y - 1].second == true) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if (exists) {
        if (dir == 0) {
            maze_[x][y].first = true;
        }
        if (dir == 1) {
            maze_[x][y].second = true;
        }
    } else {
        if (dir == 0) {
            maze_[x][y].first = false;
        }
        if (dir == 1) {
            maze_[x][y].second = false;
        }
    }
}

cs225::PNG* SquareMaze::drawMaze() const {
    cs225::PNG* png = new cs225::PNG(width_ * 10 + 1, height_ * 10 + 1);
    for (unsigned int i = 0; i < png->width(); i++) {
        if (i == 0 || i > 9) {
            cs225::HSLAPixel& pixel = png->getPixel(i, 0);
            pixel.l = 0;
        }
    }
    for (unsigned int i = 0; i < png->height(); i++) {
        cs225::HSLAPixel& pixel = png->getPixel(0, i);
        pixel.l = 0;
    }
    for (int x = 0; x < width_; x++) {
        for (int y = 0; y < height_; y++) {
            if (maze_[x][y].first == true) {
                for (int k = 0; k <= 10; k++) {
                    cs225::HSLAPixel& pixel = png->getPixel((x + 1) * 10, y * 10 + k);
                    pixel.l = 0;
                }
            }
            if (maze_[x][y].second == true) {
                for (int k = 0; k <= 10; k++) {
                    cs225::HSLAPixel& pixel = png->getPixel(x * 10 + k, (y + 1) * 10);
                    pixel.l = 0;
                }
            }
        }
    }
    return png;
}

std::vector<int> SquareMaze::solveMaze() {
    std::vector<int> length(width_);
    std::map<std::pair<int, int>, int> map; // (x,y) -> last point's direction to (x,y) 0,1,2,3
    std::map<std::pair<int, int>, int> levels;
    std::queue<std::pair<int, int>> to_visit;
    std::map<std::pair<int, int>, bool> visited;
    // std::pair<int, int> target(i, height_ - 1);
    std::pair<int, int> start(0, 0);
    to_visit.push(start);
    levels[start] = 0;
    while (!to_visit.empty()) {
        //std::cout << "get into while loop" << std::endl;
        std::pair<int, int> cur = to_visit.front();
        to_visit.pop();
        visited[cur] = true;
        if (canTravel(cur.first, cur.second, 0)) {
            std::pair<int, int> next(cur.first + 1, cur.second);
            if (visited.count(next) > 0) {

            } else {
                to_visit.push(next);
                map[next] = 0;
                levels[next] = levels[cur] + 1;
            }
        }
        if (canTravel(cur.first, cur.second, 1)) {
            std::pair<int, int> next(cur.first, cur.second + 1);
            if (visited.count(next) > 0) {

            } else {
                to_visit.push(next);
                map[next] = 1;
                levels[next] = levels[cur] + 1;
            }
        }
        if (canTravel(cur.first, cur.second, 2)) {
            std::pair<int, int> next(cur.first - 1, cur.second);
            if (visited.count(next) > 0) {

            } else {
                to_visit.push(next);
                map[next] = 2;
                levels[next] = levels[cur] + 1;
            }
        }
        if (canTravel(cur.first, cur.second, 3)) {
            std::pair<int, int> next(cur.first, cur.second - 1);
            if (visited.count(next) > 0) {

            } else {
                to_visit.push(next);
                map[next] = 3;
                levels[next] = levels[cur] + 1;
            }
        }
    }
    std::cout << "finished BFS" << std::endl;
    // calculate the path length to each point at last row and find the max length and corresponding end_point
    for (int i = 0; i < width_; i++) {
        std::pair<int, int> target(i, height_ - 1);
        length[i] = levels[target];
    }
    int max_level = *std::max_element(length.begin(), length.end());
    std::pair<int, int> end_point;
    for (int i = 0; i < width_; i++) {
        std::pair<int, int> temp(i, height_ - 1);
        if (levels[temp] == max_level) {
            end_point = temp;
            break;
        }
    }
    exit_ = end_point;
    // use the map to backtrack the path to the end_point
    std::vector<int> path;
    std::pair<int, int> cur = end_point;
    while (cur != start) {
        int dir = map[cur];
        if (dir == 0) {
            path.push_back(dir);
            cur.first -= 1;
        }
        if (dir == 1) {
            path.push_back(dir);
            cur.second -= 1;
        }
        if (dir == 2) {
            path.push_back(dir);
            cur.first += 1;
        }
        if (dir == 3) {
            path.push_back(dir);
            cur.second += 1;
        }
    }
    std::reverse(path.begin(), path.end());
    return path;
}

cs225::PNG* SquareMaze::drawMazeWithSolution() {
    cs225::PNG* png = drawMaze();
    std::vector<int> path = solveMaze();
    std::pair<int, int> cur(5, 5);
    for (unsigned int i = 0; i < path.size(); i++) {
        int dir = path[i];
        if (dir == 0) {
            for (int i = 0; i < 10; i++) {
                cs225::HSLAPixel &curPixel = png->getPixel(cur.first, cur.second);
                curPixel.h = 0;
                curPixel.s = 1;
                curPixel.l = 0.5;
                cur.first += 1;
            }
        }
        if (dir == 1) {
            for (int i = 0; i < 10; i++) {
                cs225::HSLAPixel &curPixel = png->getPixel(cur.first, cur.second);
                curPixel.h = 0;
                curPixel.s = 1;
                curPixel.l = 0.5;
                cur.second += 1;
            }
        }
        if (dir == 2) {
            for (int i = 0; i < 10; i++) {
                cs225::HSLAPixel &curPixel = png->getPixel(cur.first, cur.second);
                curPixel.h = 0;
                curPixel.s = 1;
                curPixel.l = 0.5;
                cur.first -= 1;
            }
        }
        if (dir == 3) {
            for (int i = 0; i < 10; i++) {
                cs225::HSLAPixel &curPixel = png->getPixel(cur.first, cur.second);
                curPixel.h = 0;
                curPixel.s = 1;
                curPixel.l = 0.5;
                cur.second -= 1;
            }
        }
    }
    cs225::HSLAPixel &curPixel = png->getPixel(cur.first, cur.second);
    curPixel.h = 0;
    curPixel.s = 1;
    curPixel.l = 0.5;

    for (int k = 1; k < 10; k++) {
        cs225::HSLAPixel& curPixel = png->getPixel(exit_.first * 10 + k, (exit_.second + 1) * 10);
        curPixel.a = 1;
        curPixel.l = 1;
    }
    return png;
}
