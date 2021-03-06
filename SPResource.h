#ifndef _SPResource_H
#define _SPResource_H

#include "ExternalLibs.h"


namespace Pei
{
	namespace Graphic
	{
		class SPTexture;
		class SPRenderer;
		class SPMesh;
	}
	class SPResourceManager;
	/// یک ریسورس نوعی است که قرار است توسط ریسورس منیجر مدیریت شود
	/// یک ریسورس معمولا از یک فایل بارگزاری می شود و ممکن است در حین اجرای برنامه لازم شود دوباره آن را بارگزاری کرد
	/// و همچنین در جایی از برنامه آن را آزاد کرد
	/// تمام این کار ها را ریسورس منیجر انجام می دهد
	/// مش و تکسچر به عنوان نمونه از ریسور ارث می برند
	class SPResource abstract
	{
		friend class SPResourceManager;
		unsigned char resGroupID;
		SPResource* next;
		SPResource* prev;
	public:
		enum Types : unsigned char
		{
			Type_Resource = 0,
			Type_Texture,
			Type_Mesh,
			Type_Renderer,
			Type_Sound,
		};
	protected:
		SPResource(Types type);
		virtual void releaseRes() = 0;
		virtual void reloadRes() = 0;
	public:
		Types type;
		std::string name;
	};
	/// ایده ریسورس منیجر بارگزاری یک منبع و دسترسی به آن به طور نامحدود است.
	/// همچنین مدیریت دیواس لاست در دایرکت تریدی
	class SPResourceManager
	{
		friend class SPResource;
		friend class Graphic::SPRenderer;
	private:
		static unsigned char resGroupID;
		static void releaseAllResources();
		static void reloadAllResources();
	public:
		static std::string basePath;
		/// اگر مش قبلا لود شده باشد اشاره گر به منبع قبلی را بر می گرداند
		/// و اگر قبلا لود نشده باشد آن را لود می کند
		static Graphic::SPMesh* GetMesh(const char* name);
		static Graphic::SPTexture* GetTexture(const char* name);
		/// منابع با این متد می توانند گروه بندی شوند به این صورت که منابعی که بعد
		/// از این متد بارگزاری می شند شناسه گروه آنها با شماره گروه جدید ذخیره می شود
		static void SetNewResourcesGroupID(unsigned char value);
		/// با این متد یک گروه از منابع آزاد می شوند
		static void RemoveResources(unsigned char resGroupID);
	};
}
#endif