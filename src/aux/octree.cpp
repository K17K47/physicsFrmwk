#include"aux/octree.hpp"

octree::octree(){
   root = new octreeBlock();
}

octree::~octree(){
   delete root;
}

void octree::build(Vector3 *elements, T obj){
   //TODO: Implementar gerador de Octree
}

octreeNode* octree::findNode(Vector3 point) const{
   //TODO
   unsigned idx = 0, l = 0;
   octreeNode* actualNode = root;
   octreeNode* tmpNode;

   for(;(!(actualNode->isLeaf()));l++){
      tmpNode = actualNode->getNode(point);
      if(tmpNode == NULL){
         continue;
      }
      actualNode = tmpNode;
   }

   return actualNode;
}

void octreeNode::setCenter(Vector3 &center){
   pos = center;
}

void octreeNode::setSize(real size){
   sz = size;
}

Vector3 getCenter() const{
   return pos;
}

real octreeNode::getSize() const{
   return sz;
}

octreeLeaf::octreeLeaf(){
   //TODO
}

octreeLeaf::octreeLeaf(Vector3 center, real size){
   pos = center;
   sz = size;
}

octreeLeaf::octreeLeaf(Vector3 center, real size, T obj){
   pos = center;
   sz = size;
   this.obj = obj;

   empty = false;
}

bool octreeLeaf::isLeaf(){
   return true;
}

bool octreeLeaf::isEmpty(){
   return empty;
}

void octreeLeaf::setObject(T obj){
   this.obj = obj;

   empty = false;
}

T octreeLeaf::getObject(){
   return obj;
}

octreeBlock::octreeBlock(){
   //TODO
}

octreeBlock::octreeBlock(Vector3 center, real size){
   pos = center;
   sz = size;
}

octreeBlock::~octreeBlock(){
   for(unsigned i=0; i<8; i++){
      if(children[i] != NULL) delete children[i];
   }
}

bool octreeBlock::isLeaf(){
   return false;
}

unsigned octreeBlock::setNode(Vector3 position, octreeNode *node){
   unsigned idx = 0;

   if((real_abs(center[0] - position[0]) > sz/2) ||
      (real_abs(center[1] - position[1]) > sz/2) ||
      (real_abs(center[2] - position[2]) > sz/2)){
      return 8;
   }

   //x
   if(center[0] < position[0]) idx+=1;
   //y
   if(center[1] < position[1]) idx+=2;
   //z
   if(center[2] < position[2]) idx+=4;

   children[idx] = node;

   return idx;
}

void octreeBlock::setNode(unsigned idx, octreeNode* node){
   //TODO
}

void octreeBlock::eraseNode(unsigned idx){
   if(idx>=0 && idx<8){
      if(children[idx] != NULL) delete children[idx];
   }
}

octreeNode* octreeBlock::getNode(unsigned idx) const{
   if(children[idx] != NULL){
      return children[idx];
   }
}

octreeNode* octreeBlock::getNode(Vector3 point) const{
   unsigned idx = 0;

   if((real_abs(center[0] - point[0]) > sz/2) ||
      (real_abs(center[1] - point[1]) > sz/2) ||
      (real_abs(center[2] - point[2]) > sz/2)){
      return NULL;
   }

   //x
   if(center[0] < point[0]) idx+=1;
   //y
   if(center[1] < point[1]) idx+=2;
   //z
   if(center[2] < point[2]) idx+=4;

   if(children[idx] != NULL){
      return children[idx];
   }

   return NULL;
}
