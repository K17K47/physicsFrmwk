#ifndef SLOTMAP_HPP_
#define SLOTMAP_HPP_

#include<vector>

template<class T>
class slotMap{
   std::vector<T> data;
   std::vector<unsigned> bRef;
   std::vector<unsigned> indir;
   std::vector<unsigned> free;

   // Insertion and erasing of elements
   unsigned insert(T item);   // Returns object ID
   void erase(unsigned idx);  // Uses object ID

   // Overload for access using object ID
   T& operator[](const unsigned idx);
   const T& operator[](const unsigned idx);

   // Direct Data access
   T& get(const unsigned idx);
   const T& get(const unsigned idx);
};

#endif
