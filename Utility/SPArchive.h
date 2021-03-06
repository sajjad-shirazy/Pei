#ifndef _SPArchive_H
#define _SPArchive_H

#include <stdarg.h>
#include "SPMutex.h"
#include "SPSerializable.h"

namespace Pei
{
	namespace Utility
	{
		/// کلاس آرشیو برای سریال کردن اشیاء استفاده می شود
		class SPArchive
		{
		public:
			enum IOType
			{
				IO_Output,
				IO_Input
			};
		private:
			std::fstream*   file;
			unsigned int    totalBytes;
			SPMutex 	    mutex;
		public:
			IOType          ioType;
			SPArchive(const char* filename,IOType ioType);
			~SPArchive();
			void          Close();
			/// تعداد بایت هایی که تا به حال ذخیره شده اند
			unsigned int  GetCurrentByte();
			/// اندازه فایل : برای مد اینپوت کاربرد دارد
			unsigned int  GetTotalBytes(){return this->totalBytes;}
			void          SaveBinary(void* mem,unsigned int size);
			void          LoadBinary(void* mem,unsigned int size);
			template<typename Type>
			void operator& (Type& object){Serialize(*this,object);}
		};
		/// متد های سریالایز نوع داده های مختلف را سریالی می کنند
		void Serialize(SPArchive& archive,int& object);
		void Serialize(SPArchive& archive,bool& object);
		void Serialize(SPArchive& archive,char& object);
		void Serialize(SPArchive& archive,long& object);
		void Serialize(SPArchive& archive,short& object);
		void Serialize(SPArchive& archive,float& object);
		void Serialize(SPArchive& archive,double& object);
		void Serialize(SPArchive& archive,std::string& object);
		void Serialize(SPArchive& archive,unsigned int& object);
		void Serialize(SPArchive& archive,unsigned long& object);
		void Serialize(SPArchive& archive,unsigned char& object);
		void Serialize(SPArchive& archive,unsigned short& object);
		void Serialize(SPArchive& archive,SPSerializable& object);

		template<typename Type>void Serialize(SPArchive& archive,std::vector<Type*>& object)
		{
			unsigned short size = object.size();
			archive & size;
			switch(archive.ioType)
			{
			case SPArchive::IO_Output:
				{
					std::vector<Type*>::iterator iter = object.begin();
					while( iter != object.end())
							archive & (**iter++);
					break;
				}
			case SPArchive::IO_Input:
				{
					while(size-->0)
					{
						Type* member = new Type();
						archive & (*member);
						object.push_back(member);
					}
					break;
				}
			}
		}
	}
}
#define ISPOINTER(Type) (typeid(Type).name()[strlen(typeid(Type).name())-1] == '*')
#define SERIALIZE_ENUM(archive,Type,value) {int p=(int)value;archive&p;value=(Type)p;}
#define SERIALIZE_OBJECT(archive,object) {switch(archive.ioType){case SPArchive::IO_Output:archive.SaveBinary(&object,sizeof(object));break;case SPArchive::IO_Input:archive.LoadBinary(&object,sizeof(object));break;}}
#endif