#ifndef OCTREE_HPP_
#define OCTREE_HPP_

#include"aux/math.hpp"

class octreeNode{
   public:
   octreeNode* parent;
   Vector3 pivot;
   real sz;

   virtual bool isLeaf()=0;
};

template<typename T>
class octreeBranch : public octreeNode{
   public:
   octreeNode* children[8];

   octreeBranch(Vector3 center, real size, octreeBranch* parentNode);
   int insert(T obj, Vector3 pos);
   void split(unsigned idx);

   bool isLeaf();

   unsigned locate(Vector3 pos);
};

template<typename T>
class octreeLeaf : public octreeNode{
   public:
   T obj;
   Vector3 objPos;

   octreeLeaf(Vector3 center, real size, octreeBranch<T>* parentNode);
   bool empty = true;
   bool isLeaf();
};

template <typename T>
class octree{
   public:
   octreeBranch<T>* root;

   octree(Vector3 center, real sz);
   int build(std::vector<T> obj, std::vector<Vector3> pos);
};

#include"octree.tpp"

#endif
