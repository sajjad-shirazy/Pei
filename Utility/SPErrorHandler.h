#ifndef _SPErrorHandler_H
#define _SPErrorHandler_H


#include "../ExternalLibs.h"

namespace Pei
{
	namespace Utility
	{
		class SPErrorHandler
		{
			std::string logFilePath;
			bool logingEnabled;
		public:
			std::list<std::string> errorsStack;

			SPErrorHandler();
			~SPErrorHandler();
			/// پیغام می دهد و از برنامه خارج می شود
			void PushError(const char* partName,const char* instanseName,const char* message);
			/// پیغام می دهد - خارج نمی شود
			void PushEvent(const char* partName,const char* instanseName,const char* message);
			void SetLogFilePath(char* path){this->logFilePath = path;}
			void SetLogingEnabled(bool value){this->logingEnabled = value;}
		};
		extern SPErrorHandler errorHandler;
	}
}

#endif