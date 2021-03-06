#ifndef _SPRenderingParameters_H
#define _SPRenderingParameters_H

#include "SPVector3.h"
using namespace Pei::Utility;

namespace Pei{
	namespace Graphic
	{
		struct SPMaterial : D3DMATERIAL9
		{
			SPMaterial();
			inline void Set(float r,float g, float b,float a){this->Diffuse.r = r;this->Diffuse.g = g;this->Diffuse.b = b;this->Diffuse.a = a;this->Ambient = this->Diffuse;}
		};
		class SPMesh;
		/// این کلاس مشخص می کند یک مش کجا و چطور رسم شود
		/// این کلاس می تواند بهینه تر شود - اگر بر پایه ماتریس پیاده شود
		struct SPRenderingParameters: public SPSerializable
		{
			friend class SPMesh;
			enum BlendingMode : unsigned char
			{
				BlendingMode_Normal = 0,
				BlendingMode_Darken,
				BlendingMode_Multiply,
				BlendingMode_Lighten,
				BlendingMode_Screen,
				BlendingMode_LinearDodge,
			};
		private:
		protected:
			void serializeBase_SPRenderingParameters(SPArchive& archive);
			virtual void serialize(SPArchive& archive);
		public:
			SPVector3               scale;
			SPVector3               rotation;
			SPVector3               position;
			//SPVector3             centerPoint;
			BlendingMode			blendMode;
			SPMaterial              material;
			bool                    visible;
			//bool                    flagRSCP;

			/// مولفه های گلوبال مشخصه ها در فضای جهانی اند
			SPVector3               global_scale;
			SPVector3               global_rotation;
			SPVector3               global_position;
			BlendingMode			global_blendMode;
			SPMaterial              global_material;

			SPRenderingParameters();
			/// با این متد مولفه ها به مولفه های جهانی منتقل می شوند
			inline void Transform(SPRenderingParameters* value = 0);
			void operator =(const SPRenderingParameters&);
		};

		void SPRenderingParameters::Transform(SPRenderingParameters* value)
		{
			if(!value)
			{
				this->global_position = this->position;
				this->global_rotation = this->rotation;
				this->global_blendMode = this->blendMode;
				this->global_material = this->material;
				this->global_scale = this->scale;
			}
			else
			{
				this->global_position = this->position + value->global_position;
				this->global_rotation = this->rotation ;//+ value->global_rotation;
				if(value->global_blendMode)
					this->global_blendMode = value->global_blendMode;
				else
					this->global_blendMode = this->blendMode;

				this->global_material = this->material;
				//this->global_material.Ambient.a = this->material.Ambient.a * value->global_material.Ambient.a;
				this->global_material.Diffuse.a = this->material.Diffuse.a * value->global_material.Diffuse.a;
				this->global_scale.x = this->scale.x * value->global_scale.x;
				this->global_scale.y = this->scale.y * value->global_scale.y;
				this->global_scale.z = this->scale.z * value->global_scale.z;
			}

		}

	}
}
#endif