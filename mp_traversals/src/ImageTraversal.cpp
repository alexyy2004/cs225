#include <cmath>
#include <iterator>
#include <iostream>
#include <vector>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

namespace Traversals {
  /**
  * Calculates a metric for the difference between two pixels, used to
  * calculate if a pixel is within a tolerance.
  *
  * @param p1 First pixel
  * @param p2 Second pixel
  * @return the difference between two HSLAPixels
  */
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt((h*h) + (s*s) + (l*l));
  }
  
  /**
  * Adds a Point for the bfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void bfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_back(point);
  }

  /**
  * Adds a Point for the dfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void dfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_back(point);
  }

  /**
  * Removes the current Point in the bfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void bfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    work_list.pop_front();
  }

  /**
  * Removes the current Point in the dfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void dfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    work_list.pop_back();
  }

  /**
   * Returns the current Point in the bfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point bfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    Point peek = work_list.front();
    return peek;
  }

  /**
   * Returns the current Point in the dfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point dfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    Point peek = work_list.at(work_list.size() - 1);
    return peek;
  }

  /**
  * Initializes a ImageTraversal on a given `png` image,
  * starting at `start`, and with a given `tolerance`.
  * @param png The image this traversal is going to traverse
  * @param start The start point of this traversal
  * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
  * it will not be included in this traversal
  * @param fns the set of functions describing a traversal's operation
  */
  ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, TraversalFunctions fns) {  
    /** @todo [Part 1] */
    png_ = png;
    start_ = start;
    tolerance_ = tolerance;
    fns_ = fns;
    visited = std::vector<std::vector<bool>>(png_.width(), std::vector<bool>(png_.height(), false));
  }

  /**
  * Returns an iterator for the traversal starting at the first point.
  */
  ImageTraversal::Iterator ImageTraversal::begin() {
    /** @todo [Part 1] */
    return ImageTraversal::Iterator(this, start_);
  }

  /**
  * Returns an iterator for the traversal one past the end of the traversal.
  */
  ImageTraversal::Iterator ImageTraversal::end() {
    /** @todo [Part 1] */
    return ImageTraversal::Iterator();
  }

  /**
  * Default iterator constructor.
  */
  ImageTraversal::Iterator::Iterator() : traversal_() {
    /** @todo [Part 1] */
  }

  ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, Point start) 
  : traversal_(traversal), start_(start){
    work_list_.push_back(start);
    cur_ = traversal_->fns_.peek(work_list_);
  }

  // bool ImageTraversal::Iterator::checkVisited(std::vector<Point> vec, Point p) {
  //   for (Point v : vec) {
  //     if (v == p) {
  //       return true;
  //     }
  //   }
  //   return false;
  // }

  /**
  * Iterator increment operator.
  *
  * Advances the traversal of the image.
  */
  ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    /** @todo [Part 1] */

    // for (Point p : work_list_) {
    //   std::cout << "point in wl: " << p.x << ", " << p.y << std::endl;
    // }
    Point right(cur_.x + 1, cur_.y);
    Point below(cur_.x, cur_.y + 1);
    Point left(cur_.x - 1, cur_.y);
    Point above(cur_.x, cur_.y - 1);
    traversal_->fns_.pop(work_list_);
    // for (Point p : work_list_) {
    //   std::cout << "point in wl after pop: " << p.x << ", " << p.y << std::endl;
    // }
    traversal_->visited[cur_.x][cur_.y] = true;
    // std::cout << "cur: " << cur_.x << ", " << cur_.y << std::endl;

    HSLAPixel start = traversal_->png_.getPixel(start_.x, start_.y);
    if (right.x >= 0 && right.x < traversal_->png_.width()) {
      HSLAPixel r = traversal_->png_.getPixel(right.x, right.y);
      double delta = calculateDelta(start, r);
      if (delta < traversal_->tolerance_ && !traversal_->visited[right.x][right.y]) {
        traversal_->fns_.add(work_list_, right);
        // std::cout << "ADD RIGHT" << std::endl;
      }
    }

    if (below.y >= 0 && below.y < traversal_->png_.height()) {
      HSLAPixel b = traversal_->png_.getPixel(below.x, below.y);
      double delta = calculateDelta(start, b);
      if (delta < traversal_->tolerance_ && !traversal_->visited[below.x][below.y]) {
        traversal_->fns_.add(work_list_, below);
        // std::cout << "ADD BELOW" << std::endl;
      }
    }

    if (left.x >= 0 && left.x < traversal_->png_.width()) {
      HSLAPixel l = traversal_->png_.getPixel(left.x, left.y);
      double delta = calculateDelta(start, l);
      if (delta < traversal_->tolerance_ && !traversal_->visited[left.x][left.y]) {
        traversal_->fns_.add(work_list_, left);
        // std::cout << "ADD LEFT" << std::endl;
      }
    }

    if (above.y >= 0 && above.y < traversal_->png_.height()) {
      HSLAPixel a = traversal_->png_.getPixel(above.x, above.y);
      double delta = calculateDelta(start, a);
      if (delta < traversal_->tolerance_ && !traversal_->visited[above.x][above.y]) {
        traversal_->fns_.add(work_list_, above);
        // std::cout << "ADD ABOVE" << std::endl;
      }
    }

    if (work_list_.empty()) {
      traversal_ = nullptr;
      // std::cout << "worklist is empty" << std::endl;
      return *this;
    }

    cur_ = traversal_->fns_.peek(work_list_);
    // std::cout << "(after add)cur: " << cur_.x << ", " << cur_.y << std::endl;

    while (traversal_->visited[cur_.x][cur_.y]) {
      traversal_->fns_.pop(work_list_);
      if (work_list_.empty()) {
        traversal_ = nullptr;
        // std::cout << "worklist is empty" << std::endl;
        return *this;
      }
      cur_ = traversal_->fns_.peek(work_list_);
    }
    return *this;
  }

  /**
  * Iterator accessor operator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
  Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    return cur_;
  }

  /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    /** @todo [Part 1] */
    if (this->traversal_ == nullptr && other.traversal_ == nullptr) {
      return false;
    } else {
      return true;
    }
  }

  /**
   * Iterator size function.
   *
   * @return size_t the size of the iterator work queue.
   */
  size_t ImageTraversal::Iterator::size() const {
    return work_list_.size();
  }

  /**
   * Iterator empty function.
   *
   * @return bool whether the iterator work queue is empty.
   */
  bool ImageTraversal::Iterator::empty() const {
    return work_list_.empty();
  }

}