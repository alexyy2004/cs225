/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim)
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] != second[curDim]) {
      return first[curDim] < second[curDim];
    }
    return first < second;
}

template <int Dim>
bool shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential)
{
    /**
     * @todo Implement this function!
     */
    int cur_dis = 0;
    int pot_dis = 0;
    for (int i = 0; i < Dim; i++) {
      cur_dis += (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
    }
    for (int i = 0; i < Dim; i++) {
      pot_dis += (potential[i] - target[i]) * (potential[i] - target[i]);
    }
    if (cur_dis != pot_dis) {
      return cur_dis > pot_dis;
    }
    return currentBest > potential;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if (newPoints.empty()) {
      root = nullptr;
      size = 0;
    } else {
      vector<Point<Dim>> points = newPoints;
      root = buildTree(0, points.size() - 1, 0, points);
      size = newPoints.size();
    }
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(int left, int right, int d, vector<Point<Dim>>& points) {
  if (left > right) {
    return nullptr;
  }
  int median = std::floor((left + right) / 2);

  auto cmp = [d](const Point<Dim>& a, const Point<Dim>& b) {
    return smallerDimVal(a, b, d);
  };

  select(points.begin() + left, points.begin() + right + 1, points.begin() + median, cmp);
  KDTreeNode* subroot = new KDTreeNode(points[median]);
  subroot->left = buildTree(left, median - 1, (d + 1) % Dim, points);
  subroot->right = buildTree(median + 1, right, (d + 1) % Dim, points);

  return subroot;
}

template <int Dim>
void KDTree<Dim>::copy(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  KDTreeNode* other_root = other.root;
  if (other_root == nullptr) {
    return;
  }
  KDTreeNode* newNode = new KDTreeNode(other_root->point);
  newNode->left = copy(other_root->left);
  newNode->right = copy(other_root->right);
  root = newNode;
  size = other.size;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copy(other);
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode *root) {
  if (root == nullptr) {
    return;
  }
  if (root->left != nullptr) {
    clear(root->left);
  }
  if (root->right != nullptr) {
    clear(root->right);
  }
  delete root;  
  root = nullptr;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this == &rhs) {
    return *this;
  }
  clear(root);
  copy(rhs);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    double bestDistance = std::numeric_limits<double>::max();
    const Point<Dim>* bestPoint = nullptr;
    findNeighborHelper(query, root, 0, bestDistance, bestPoint);
    return *bestPoint;
}

template <int Dim>
void KDTree<Dim>::findNeighborHelper(const Point<Dim>& target, KDTreeNode* curnode, int depth, double& bestDistance, const Point<Dim>*& bestPoint) const {
  if (curnode == nullptr) {
    return;
  }
  //update bestPoint and bestDistance
  double diff = 0;
  const Point<Dim>& curnode_point = curnode->point;
  for (int i = 0; i < Dim; i++) { // i < Dim
    double temp = target[i] - curnode_point[i];
    diff = diff + temp * temp;
  }
  if (diff < bestDistance || (diff == bestDistance && curnode_point < *bestPoint)) {
    bestDistance = diff;
    bestPoint = &curnode_point;
  }

  //go down tree recursion
  KDTreeNode* first = nullptr;
  KDTreeNode* second = nullptr;
  int cur_dim = depth % Dim;
  if (smallerDimVal(target, curnode_point, cur_dim)) {
    first = curnode->left;
    second = curnode->right;
  } else {
    first = curnode->right;
    second = curnode->left;
  }
  findNeighborHelper(target, first, depth + 1, bestDistance, bestPoint);
  
  //back tracking
  double radius = 0.0;
  radius += (curnode_point[cur_dim] - target[cur_dim]) * (curnode_point[cur_dim] - target[cur_dim]);
  // for (int i = 0; i < Dim; i++) {
  //   radius += (bestPoint[i] - target[i]) * (bestPoint[i] - target[i]);
  // }
  if (bestDistance > radius || (bestDistance == radius && curnode_point < *bestPoint)) {
    findNeighborHelper(target, second, depth + 1, bestDistance, bestPoint);
  }
}

template <typename RandIter, typename Comparator>
RandIter partition(RandIter start, RandIter end, RandIter k, Comparator cmp)
{
    /**
     * @todo Implement this function!
     */    
    std::iter_swap(end - 1, k);
    RandIter temp = start;
    for (RandIter it = start; it != end - 1; it++) {
      if (cmp(*it, *(end - 1))) {
        std::iter_swap(it, temp);
        temp++;
      }
    }
    std::iter_swap(end - 1, temp);
    return temp;
}

template <typename RandIter, typename Comparator>
void select(RandIter start, RandIter end, RandIter k, Comparator cmp)
{
    /**
     * @todo Implement this function!
     */    
    if (start == end) {
      return;
    } else {
      RandIter pivot = partition(start, end, k, cmp);
      if (pivot == k) {
        return;
      } else if (k < pivot) {
        return select(start, pivot, k, cmp);
      } else {
        return select(pivot + 1, end, k, cmp);
      }
    }
}

