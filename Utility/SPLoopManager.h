#ifndef _SPLoopManager_H
#define _SPLoopManager_H

#include "SPTimer.h"

namespace Pei
{
	namespace Utility
	{
		class SPTimer;	
		/// ایده لوپ منیجر تعیین یک نرخ پریود و استراحت در وقت اضافه بود
		/// با یک لوپ منیجر می شود اف پی اس راهم بدست آورد
		class SPLoopManager
		{
			SPTimer _loopTimer;
			bool _allowSleep;
			unsigned char _resulation,_loopCounter,_sleepLenght;
			unsigned short _periodRate;
			double _pps;
		public:
			SPLoopManager();

			void BeginLoop();
			void EndLoop();

			double GetPPS(){return this->_pps;}

			void SetResulation(unsigned char value){this->_resulation = value;}
			unsigned char GetResulation(){return this->_resulation;}

			void AllowSleep(bool allowed,unsigned short periodRate = 60){this->_periodRate = periodRate ; this->_allowSleep = allowed;}		
		};
	}
}

#endif