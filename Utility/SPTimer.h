#ifndef _SPTimer_H
#define _SPTimer_H

#include "../ExternalLibs.h"
namespace Pei
{
	namespace Utility
	{
		/// کلاس تامیر افتضاح است و باید اصلاح اساسی شود
		class SPTimer
		{
		public:

			SPTimer();

			void Start();
			void Stop();
			void Reset();
			void Pause();
			void MemorizeThisTime();
			unsigned int GetTime();
			unsigned int GetMemory();
			unsigned int GetTimePassedFromMemory();


		private:
			bool _running;
			unsigned int _delta;
			unsigned int _memory;
			unsigned int _baseTime;
		};
	}
}

#endif