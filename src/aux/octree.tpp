template <typename T>
octreeBranch<T>::octreeBranch(Vector3 center, real size, octreeBranch<T>* parentNode){
   Vector3 tmp;
   real halfSz = size/2;
   real quarterSz = size/4;
   parent = parentNode;
   pivot = center;
   sz = size;

   for(int i=0; i<8; i++){
      tmp = center;

      //x
      if( i&1 ){
         tmp[0]+=quarterSz;
      }else{
         tmp[0]-=quarterSz;
      }
      //y
      if( i&2 ){
         tmp[1]+=quarterSz;
      }else{
         tmp[1]-=quarterSz;
      }
      //z
      if( i&4 ){
         tmp[2]+=quarterSz;
      }else{
         tmp[2]-=quarterSz;
      }

      children[i] = new octreeLeaf<T>(tmp, halfSz, this);
   }
}

template <typename T>
bool octreeBranch<T>::isLeaf() {return false;}

template <typename T>
unsigned octreeBranch<T>::locate(Vector3 pos){
   unsigned idx = 0;

   if((real_abs(pivot[0] - pos[0]) > sz/2) ||
      (real_abs(pivot[1] - pos[1]) > sz/2) ||
      (real_abs(pivot[2] - pos[2]) > sz/2)){
      return 8;
   }

   //x
   if(pivot[0] < pos[0]) idx+=1;
   //y
   if(pivot[1] < pos[1]) idx+=2;
   //z
   if(pivot[2] < pos[2]) idx+=4;

   return idx;
}

template <typename T>
int octreeBranch<T>::insert(T obj, Vector3 pos){
   unsigned idx = locate(pos);

   if(idx==8) return -1;

   if(children[idx]->isLeaf()){
      if(dynamic_cast<octreeLeaf<T>*>(children[idx])->empty){
         dynamic_cast<octreeLeaf<T>*>(children[idx])->empty = false;
         dynamic_cast<octreeLeaf<T>*>(children[idx])->obj = obj;
         dynamic_cast<octreeLeaf<T>*>(children[idx])->objPos = pos;
         return 0;
      }else{
         split(idx);
         return dynamic_cast<octreeBranch<T>*>(children[idx])->insert(obj, pos);
      }
   }else{
      return dynamic_cast<octreeBranch<T>*>(children[idx])->insert(obj, pos);
   }
}

template <typename T>
void octreeBranch<T>::split(unsigned idx){
   octreeLeaf<T> tmp = *dynamic_cast<octreeLeaf<T>*>(children[idx]);
   delete children[idx];
   children[idx] = new octreeBranch<T>(tmp.pivot, tmp.sz, this);
   dynamic_cast<octreeBranch*>(children[idx])->insert(tmp.obj, tmp.objPos);
}

template <typename T>
octreeLeaf<T>::octreeLeaf(Vector3 center, real size, octreeBranch<T>* parentNode){
   parent = parentNode;
   pivot = center;
   sz = size;
}

template <typename T>
bool octreeLeaf<T>::isLeaf() {return true;}

template <typename T>
octree<T>::octree(Vector3 center, real sz){
   root = new octreeBranch<T>(center, sz, nullptr);
}

template <typename T>
int octree<T>::build(std::vector<T> obj, std::vector<Vector3> pos){
   for(int i=0; i<obj.size(); i++){
      if(root->insert(obj[i], pos[i])) return -1;
   }
   return 0;
}
