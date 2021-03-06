#include <cmath>
#include <algorithm>
#include <glm/gtx/norm.hpp>
#include "noise.h"

#define TwoPi 6.28318530718

template<class T>
inline void get_barycentric(T x, int &i, T &f, int i_low, int i_high)
{
   double s=std::floor(x);
   i=(int)s;
   if(i<i_low){
      i=i_low;
      f=0;
   }else if(i>i_high-2){
      i=i_high-2;
      f=1;
   }else{
      f=(T)(x-s);
   }
}

template<class S,class T>
inline S lerp(const S &value0, const S &value1, T f)
{ return (1-f)*value0 + f*value1; }

template<class S,class T>
inline S bilerp(const S &v00, const S &v10, 
                const S &v01, const S &v11, 
                T fx, T fy)
{ 
   return lerp(    
               lerp(v00, v10, fx),
               lerp(v01, v11, fx), 
               fy);
}

template<class S,class T>
inline S trilerp(
   const S& v000, const S& v100,
   const S& v010, const S& v110,
   const S& v001, const S& v101,  
   const S& v011, const S& v111,
   T fx, T fy, T fz) 
{
   return lerp(
            bilerp(v000, v100, v010, v110, fx, fy),
            bilerp(v001, v101, v011, v111, fx, fy),
            fz);
}

template<class S,class T>
inline S quadlerp(
   const S& v0000, const S& v1000,
   const S& v0100, const S& v1100,
   const S& v0010, const S& v1010,  
   const S& v0110, const S& v1110,
   const S& v0001, const S& v1001,
   const S& v0101, const S& v1101,
   const S& v0011, const S& v1011,  
   const S& v0111, const S& v1111,
   T fx, T fy, T fz, T ft) 
{
   return lerp(
            trilerp(v0000, v1000, v0100, v1100, v0010, v1010, v0110, v1110, fx, fy, fz),
            trilerp(v0001, v1001, v0101, v1101, v0011, v1011, v0111, v1111, fx, fy, fz),
            ft);
}

static glm::vec3 sample_sphere(unsigned int& seed)
{
   glm::vec3 v;
   float m2;
   do {
      for(unsigned int i=0; i<3; ++i){
         v[i]=randhashf(seed++,-1,1);
      }
	  m2 = glm::length2(v);
   } while (m2>1 || m2==0);
   return v / std::sqrt(m2);
}

Noise3::
Noise3(unsigned int seed)
{
   for(unsigned int i=0; i<n; ++i){
      basis[i]=sample_sphere(seed);
      perm[i]=i;
   }
   reinitialize(seed);
}

void Noise3::
reinitialize(unsigned int seed)
{
   for(unsigned int i=1; i<n; ++i){
      int j=randhash(seed++)%(i+1);
      std::swap(perm[i], perm[j]);
   }
}

float Noise3::
operator()(float x, float y, float z) const
{
   float floorx=std::floor(x), floory=std::floor(y), floorz=std::floor(z);
   int i=(int)floorx, j=(int)floory, k=(int)floorz;
   const glm::vec3 &n000=basis[hash_index(i,j,k)];
   const glm::vec3 &n100=basis[hash_index(i+1,j,k)];
   const glm::vec3 &n010=basis[hash_index(i,j+1,k)];
   const glm::vec3 &n110=basis[hash_index(i+1,j+1,k)];
   const glm::vec3 &n001=basis[hash_index(i,j,k+1)];
   const glm::vec3 &n101=basis[hash_index(i+1,j,k+1)];
   const glm::vec3 &n011=basis[hash_index(i,j+1,k+1)];
   const glm::vec3 &n111=basis[hash_index(i+1,j+1,k+1)];
   float fx=x-floorx, fy=y-floory, fz=z-floorz;
   float sx=fx*fx*fx*(10-fx*(15-fx*6)),
         sy=fy*fy*fy*(10-fy*(15-fy*6)),
         sz=fz*fz*fz*(10-fz*(15-fz*6));
   return trilerp(    fx*n000.x +     fy*n000.y +     fz*n000.z,
                  (fx-1)*n100.x +     fy*n100.y +     fz*n100.z,
                      fx*n010.x + (fy-1)*n010.y +     fz*n010.z,
                  (fx-1)*n110.x + (fy-1)*n110.y +     fz*n110.z,
                      fx*n001.x +     fy*n001.y + (fz-1)*n001.z,
                  (fx-1)*n101.x +     fy*n101.y + (fz-1)*n101.z,
                      fx*n011.x + (fy-1)*n011.y + (fz-1)*n011.z,
                  (fx-1)*n111.x + (fy-1)*n111.y + (fz-1)*n111.z,
                  sx, sy, sz);
}

FlowNoise3::
FlowNoise3(unsigned int seed, float spin_variation)
   : Noise3(seed)
{
   seed+=8*n; // probably avoids overlap with sequence used in initializing superclass Noise3
   for(unsigned int i=0; i<n; ++i){
      original_basis[i]=basis[i];
      spin_axis[i]=sample_sphere(seed);
      spin_rate[i]=TwoPi*randhashf(seed++, 1-0.5f*spin_variation, 1+0.5f*spin_variation);
   }
}

void FlowNoise3::
set_time(float t)
{
   for(unsigned int i=0; i<n; ++i){
      float theta=spin_rate[i]*t;
      float c=std::cos(theta), s=std::sin(theta);
      // form rotation matrix
      float R00=c+(1-c)*sqr(spin_axis[i].x),
            R01=(1-c)*spin_axis[i].x*spin_axis[i].y-s*spin_axis[i].z,
            R02=(1-c)*spin_axis[i].x*spin_axis[i].z+s*spin_axis[i].y;
      float R10=(1-c)*spin_axis[i].x*spin_axis[i].y+s*spin_axis[i].z,
            R11=c+(1-c)*sqr(spin_axis[i].y),
            R12=(1-c)*spin_axis[i].y*spin_axis[i].z-s*spin_axis[i].x;
      float R20=(1-c)*spin_axis[i].x*spin_axis[i].z-s*spin_axis[i].y,
            R21=(1-c)*spin_axis[i].y*spin_axis[i].z+s*spin_axis[i].x,
            R22=c+(1-c)*sqr(spin_axis[i].z);
      basis[i].x=R00*original_basis[i].x + R01*original_basis[i].y + R02*original_basis[i].z;
      basis[i].y=R10*original_basis[i].x + R11*original_basis[i].y + R12*original_basis[i].z;
      basis[i].z=R20*original_basis[i].x + R21*original_basis[i].y + R22*original_basis[i].z;
   }
}

