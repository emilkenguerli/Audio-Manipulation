#include <iostream>
#include "Audio.h"

namespace KNGEMI002 {
template <class T> T Audio<T>::getmax() 
{
  T retval;
  retval = a>b? a : b;
  return retval;
};

}