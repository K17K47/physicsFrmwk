#include"aux/slotmap.hpp"

template<class T>
unsigned slotMap<T>::insert(T item){
   unsigned idx;

   std::lock_guard<std::mutex> guard(mtx);

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
void slotMap<T>::erase(unsigned idx){
   std::lock_guard<std::mutex> guard(mtx);

   unsigned ind = indir[idx];

   data[ind] = data.back();
   bRef[ind] = bRef.back();
   indir[bRef.back()] = indir[idx];

   free.push_back(idx);

   bRef.pop_back();
   data.pop_back();
}

template<class T>
T& slotMap<T>::operator[](unsigned idx){
   std::lock_guard<std::mutex> guard(mtx);
   return data[indir[idx]];
}

template<class T>
T slotMap<T>::operator[](unsigned idx) const{
   return data[indir[idx]];
}

template<class T>
T& slotMap<T>::get(unsigned idx){
   std::lock_guard<std::mutex> guard(mtx);
   return data[idx];
}

template<class T>
T slotMap<T>::get(unsigned idx) const{
   return data[idx];
}

template<class T>
unsigned slotMap<T>::size(){
   return data.size();
}

template<class T>
void slotMap<T>::clear(){
   data.clear();
   indir.clear();
   bRef.clear();
   free.clear();
}
