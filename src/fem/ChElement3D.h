#ifndef CHELEMENT3D_H
#define CHELEMENT3D_H

#include "fem/ChElementGeneric.h"
#include "fem/ChGaussIntegrationRule.h"


namespace chrono{
	namespace fem{

/// Class for all 3-Dimensional elements 


class ChApi ChElement3D : public ChElementGeneric
{
protected:
	double Volume;

public:

};



//struct MatrixAndDet						// use this structure to keep in memory booth 'MatrB'  
//	{										// and Jacobian determinant (necessary for integration)
//		ChMatrixDynamic<> Matrix;			// Not necessary because we store all MatrB matrices
//		double JacobianDet;
//	};


		///
		/// Calss for tetrahedral elements
		///
class ChApi ChTetrahedron : public ChElement3D					//		  /|\						//
{																//		 / |  \						//
protected:														//		/  |	\					//
																//	   /.  |	  \					//
public:															//	   \   |.		\				//
	int ID;														//		\  |	.	  \				//
		// Computes the volume of the element					//		 \ |		.	\			//
		// (and stores the value in this->volume)				//		  \|__ __ __ __'__\			//
	virtual double ComputeVolume() = 0;
	double GetVolume() {return Volume;}
															
};																

		///
		/// Calss for hexahedral elements
		///
class ChApi ChHexahedron : public ChElement3D					//		    __ __ __ __				//
{																//		  /			  /|			//				
protected:														//		 /_|__ __ __ / |			//
	ChGaussIntegrationRule* ir;									//		|			|  |			//
	std::vector<ChGaussPoint*> GpVector;						//		|  |		|  |			//
																//		|	 __	 __	|  |			//	
																//		| /			| /				//
public:															//		|__ __ __ __|/				//
	int ID;														
																		
};																			  




	}//___end of namespace fem___
}//___end of namespace chrono___

#endif