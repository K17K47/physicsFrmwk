#ifndef OCTREE_HPP_
#define OCTREE_HPP_

template<typename T>class octree{
   private:
      octreeNode* root;

   public:
      octree();
      ~octree();

      void build(Vector3 *elements, T obj);
      octreeNode* findNode(Vector3 point) const;
};

class octreeNode{
   protected:
      Vector3 pos;
      real sz;

   public:
      virtual bool isLeaf();

      void setCenter(Vector3 center);
      void setSize(real size);

      Vector3 getCenter() const;
      real getSize() const;
};

template<typename T>
class octreeLeaf: public octreeNode{
   public://private:
      T obj;

      bool empty = true;

   public:
      octreeLeaf();
      octreeLeaf(Vector3 center, real size);
      octreeLeaf(Vector3 center, real size, T obj);

      bool isLeaf();

      bool isEmpty();

      void setObject(T obj);
      T getObject();
};

/*
*        ________       +Y
*       /   /   /|       |
*      / 2 / 3 / |       |
*     /___/___/  |       |
*    /   /   /|3 |       |
*   / 6 / 7 / | /|       |
*  /___/___/  |/ |       O-----------+X
*  |   |   |7 /1 /      /
*  | 6 | 7 | /| /      /
*  |___|___|/ |/      /
*  |   |   |5 /      /
*  | 4 | 5 | /      /
*  |___|___|/      +Z
*
*
*/


template<typename T>
class octreeBlock: public octreeNode{
   public://private:
      octreeNode* children[8];

   public:
      octreeBlock();
      octreeBlock(Vector3 center, real size);
      ~octreeBlock();

      bool isLeaf();

      unsigned setNode(Vector3 position, octreeNode* node);
      void setNode(unsigned idx, octreeNode* node);

      void eraseNode(unsigned idx);

      octreeNode* getNode(unsigned idx) const;
      octreeNode* getNode(Vector3 point) const;
};

#endif
