//////////////////////////////////////////////////
//  
//   ChPovRayAssetCustom.cpp
//
// ------------------------------------------------
// 	 Copyright:Alessandro Tasora / DeltaKnowledge
//             www.deltaknowledge.com
// ------------------------------------------------
///////////////////////////////////////////////////

     
#include "ChPovRay.h"
#include "ChPovRayAssetCustom.h"

using namespace chrono;
using namespace postprocess;


void ChPovRayAssetCustom::SetCommands (char mcomm[])
{
	this->custom_command = mcomm;
}


