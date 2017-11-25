#include"aux/slotmap.hpp"

template<class T>
unsigned slotMap::insert(T item){
   unsigned idx;

   data.push_back(item);

   if(!free.size()){
      idx = indir.size();
      indir.push_back(data.size()-1);
   }else{
      idx = free.back();
      indir[idx] = data.size()-1;
   }

   bRef.push_back(idx);

   return idx;
}

template<class T>
void slotMap::erase(unsigned idx){
   unsigned ind = indir[idx];

   data[ind] = data.back();
   bRef[ind] = bRef.back();
   indir[bRef.back()] = indir[idx];

   free.push_back(idx);

   bRef.pop_back();
   data.pop_back();
}

template<class T>
T& slotMap::operator[](unsigned idx){
   return data[indir[idx]];
}

template<class T>
const T& slotMap::operator[](unsigned idx){
   return data[indir[idx]];
}

template<class T>
T& slotMap::get(unsigned idx){
   return data[idx];
}

template<class T>
const T& slotMap::get(unsigned idx){
   return data[idx];
}
