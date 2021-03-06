#ifndef _SP3DObject_H
#define _SP3DObject_H

#include "SPVector3.h"
#include "../SPResource.h"
using namespace Pei::Utility;

#define SP_FVF_PNDT  (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define SP_FVF_PD    (D3DFVF_XYZ|D3DFVF_DIFFUSE)

namespace Pei
{
	namespace Graphic
	{
		//____________________________________________
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		struct SPVertex_PNDT
		{
			float x,y,z;
			float nx,ny,nz;
			unsigned long diffuse;
			float u,v;
		};
		struct SPVertex_PD
		{
			float x,y,z;
			unsigned long diffuse;
		};
		//____________________________________________
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		class  SPTexture;
		struct SPMaterial;
		struct SPRenderingParameters;
		//کلاس مش اساسا برای نمایش فایل های انیمیشن دو بعدی بهینه شده 
		// برای همه ساب مش ها تنها یک متربال و تکسچر دارد و این برای بهینگی بیشتر در زمان ترسیم است	
		class SPMesh: public SPResource
		{
			friend class SPResourceManager;
			SPMesh(const char* name = 0);
			~SPMesh();
			short currentSubsetIndex;
		protected:
			virtual void reloadRes();
			virtual void releaseRes();
		public:
			LPD3DXMESH heart;
			SPVector3 centerPoint;
			SPTexture* texture;
			unsigned int subsetsCount;
			///if subsetIndex == -1 All subsets will be rendered
			virtual void  Render(SPRenderingParameters* rp);
			float GetRadius(SPMesh* mesh);
			void  GetCenterPoint(SPVector3* result);
			// اینکه کدام ساب مش باید نمایش داده شود را مشخص می کند
			// با مقدار -1 همه ساب مش ها ترسیم می شوند
			void SetCurrentSubsetIndex(short value){this->currentSubsetIndex = value;}
			//void  Save(const char* resName);
			//void  CreateBillboard(SPTexture* texture,SPRect* rect = 0,SPVector3* centerPoint = 0);
			//void  SetCenterPoint(SPVector3* value);
			bool Pick(POINT* screenPoint,SPRenderingParameters* rp);
		};
	}
}
#endif