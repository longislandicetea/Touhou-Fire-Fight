#ifndef MoogeTypeH
#define MoogeTypeH
#include <math.h>
#include <string.h>

namespace MoogeType
{
	//Unique ID type for primitive object.
	typedef unsigned int PRIMITIVEID;
	//Unique ID type for camera object.
	typedef unsigned int CAMERAID;
	//Unique ID type for text objects.
	typedef unsigned int TEXTID;

	//Vector type used by Mooge.

	//== [Vector] ==

	//Struct style.
	struct VECTORFS
	{
		inline VECTORFS(): x(0.0), y(0.0), z(0.0) { }
		inline VECTORFS(float xIn, float yIn, float zIn): x(xIn), y(yIn), z(zIn) { }
		inline VECTORFS(const VECTORFS& VecIn) { memcpy(this, &VecIn, sizeof(VECTORFS)); }

		inline void Assign(const VECTORFS& VecIn) { memcpy(this, &VecIn, sizeof(VECTORFS)); }

		inline float Length()
		{
			return sqrt(x*x + y*y + z*z);
		}

		inline void AddSelf(const VECTORFS& VectorFSIn)
		{
			x = x + VectorFSIn.x;
			y = y + VectorFSIn.y;
			z = z + VectorFSIn.z;
		}

		inline VECTORFS Add(const VECTORFS& VectorFSIn)
		{
			return VECTORFS(x + VectorFSIn.x, y + VectorFSIn.y, z + VectorFSIn.z);
		}

		inline void SubSelf(const VECTORFS& VectorFSIn)
		{
			x = x - VectorFSIn.x;
			y = y - VectorFSIn.y;
			z = z - VectorFSIn.z;
		}

		inline VECTORFS Sub(const VECTORFS& VectorFSIn)
		{
			return VECTORFS(x - VectorFSIn.x, y - VectorFSIn.y, z - VectorFSIn.z);
		}

		inline void MultiSelf(const float& num)
		{
			x = x*num;
			y = y*num;
			z = z*num;
		}

		inline VECTORFS Multi(const float& num)
		{
			return VECTORFS(x*num, y*num, z*num);
		}

		inline float Dot(const VECTORFS& VectorFSIn)
		{
			return (x*VectorFSIn.x + y*VectorFSIn.y + z*VectorFSIn.z);
		}

		inline void CrossSelf(const VECTORFS& VectorFSIn)
		{
			//[Bewared]: calculate product first. Than store it.
			VECTORFS Pruduct(y*VectorFSIn.z - z*VectorFSIn.y, z*VectorFSIn.x - x*VectorFSIn.z, x*VectorFSIn.y - y*VectorFSIn.x);
			memcpy(this, &Pruduct, sizeof(VECTORFS));
		}

		inline VECTORFS Cross(const VECTORFS& VectorFSIn)
		{
			return VECTORFS(y*VectorFSIn.z - z*VectorFSIn.y, z*VectorFSIn.x - x*VectorFSIn.z, x*VectorFSIn.y - y*VectorFSIn.x);
		}

		inline void NormalizeSelf()
		{
			float magnitude = sqrt(x*x + y*y + z*z);
			if(magnitude != 0.0)
			{
				x /= magnitude;
				y /= magnitude;
				z /= magnitude;
			}else
			{
				x = 0.0;
				y = 0.0;
				z = 0.0;
			}
		}

		inline VECTORFS Normalize()
		{
			float magnitude = sqrt(x*x + y*y + z*z);
			if(magnitude != 0.0)
			{
				 return VECTORFS(x/magnitude, y/magnitude, z/magnitude);
			}else
			{
				 return VECTORFS(0.0, 0.0, 0.0);
			}
		}

		float x;
		float y;
		float z;
	};

	//Array style.
	typedef float VECTORFA[3];

	//== [Quaternion] ==
	//This thing only used by camera rotate.
	//It's a little bit tricky.
	//Ref:
	//	http://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
	struct QUATERNION
	{
		inline QUATERNION(): w(0.0), x(0.0), y(0.0), z(0.0) { }
		inline QUATERNION(float wIn, float xIn, float yIn, float zIn): w(wIn), x(xIn), y(yIn), z(zIn){ }
		inline QUATERNION(const QUATERNION& QuatIn){ memcpy(this, &QuatIn, sizeof(QUATERNION)); }

		inline void MultiSelf(const QUATERNION& QuaternionIn)
		{
			QUATERNION Result;
			Result.w = (w*QuaternionIn.w - x*QuaternionIn.x - y*QuaternionIn.y - z*QuaternionIn.z);
			Result.x = (w*QuaternionIn.x + x*QuaternionIn.w + y*QuaternionIn.z - z*QuaternionIn.y);
			Result.y = (w*QuaternionIn.y - x*QuaternionIn.z + y*QuaternionIn.w + z*QuaternionIn.x);
			Result.z = (w*QuaternionIn.z + x*QuaternionIn.y - y*QuaternionIn.x + z*QuaternionIn.w);
			memcpy(this, &Result, sizeof(QUATERNION));
		}

		inline QUATERNION Multi(const QUATERNION& QuaternionIn)
		{
			return QUATERNION
			(
			(w*QuaternionIn.w - x*QuaternionIn.x - y*QuaternionIn.y - z*QuaternionIn.z),
			(w*QuaternionIn.x + x*QuaternionIn.w + y*QuaternionIn.z - z*QuaternionIn.y),
			(w*QuaternionIn.y - x*QuaternionIn.z + y*QuaternionIn.w + z*QuaternionIn.x),
			(w*QuaternionIn.z + x*QuaternionIn.y - y*QuaternionIn.x + z*QuaternionIn.w)
			);
		}

		//[This function only used in purpose to optimize performance]
		inline VECTORFS MultiVector(const QUATERNION& QuaternionIn)
		{
			return VECTORFS
			(
			((w*QuaternionIn.x + x*QuaternionIn.w + y*QuaternionIn.z - z*QuaternionIn.y)),
			((w*QuaternionIn.y - x*QuaternionIn.z + y*QuaternionIn.w + z*QuaternionIn.x)),
			((w*QuaternionIn.z + x*QuaternionIn.y - y*QuaternionIn.x + z*QuaternionIn.w))
			);
		}

		float w;
		float x;
		float y;
		float z;
	};

	//== [Color] ==

	//Struct style.
	struct COLOR3UBS
	{
		inline COLOR3UBS(): r(0), g(0), b(0) { }
		inline COLOR3UBS(unsigned char rIn, unsigned char gIn, unsigned char bIn): r(rIn), g(gIn), b(bIn){ }
		inline COLOR3UBS(const COLOR3UBS& ColorIn){ memcpy(this, &ColorIn, sizeof(COLOR3UBS)); }

		unsigned char r;
		unsigned char g;
		unsigned char b;
	};

	//Array style.
	typedef unsigned char COLOR3UBA[3];

	//Struct style.
	struct COLOR4UBS
	{
		inline COLOR4UBS(): r(0), g(0), b(0), a(0) { }
		inline COLOR4UBS(unsigned char rIn, unsigned char gIn, unsigned char bIn, unsigned char aIn): r(rIn), g(gIn), b(bIn), a(aIn){ }

		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	};

	//Array style.
	typedef unsigned char COLOR4UBA[4];
}


#endif