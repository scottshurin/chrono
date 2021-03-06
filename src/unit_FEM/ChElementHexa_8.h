#ifndef CHELEMENTHEXA8_H
#define CHELEMENTHEXA8_H

//////////////////////////////////////////////////
//  
//   ChElementHexa_8.h
//
//   Class for hexaedrons
//
//
//   HEADER file for CHRONO,
//	 Multibody dynamics engine
//
///////////////////////////////////////////////////

#include "ChElement3D.h"
#include "ChNodeFEMxyz.h"

namespace chrono
{
namespace fem
{

class ChApiFem ChElementHexa_8 : public ChHexahedron
{
protected:
		std::vector<ChNodeFEMxyz*> nodes;
		ChSharedPtr<ChContinuumElastic> Material;
		//std::vector< ChMatrixDynamic<> > MatrB;	// matrices of shape function's partial derivatives (one for each integration point)
													// we use a vector to keep in memory all the 8 matrices (-> 8 integr. point)
													// NO! each matrix is stored in the respective gauss point

		ChMatrixDynamic<> StiffnessMatrix;

public:

	ChElementHexa_8();
	virtual ~ChElementHexa_8();

	virtual int GetNcoords() {return 24;}
	virtual int GetNnodes()  {return 8;}
	virtual ChNodeFEMbase* GetNodeN(int n) {return nodes[n];}

	virtual void SetNodes(ChNodeFEMxyz* nodeA, ChNodeFEMxyz* nodeB, ChNodeFEMxyz* nodeC, ChNodeFEMxyz* nodeD,
						  ChNodeFEMxyz* nodeE, ChNodeFEMxyz* nodeF, ChNodeFEMxyz* nodeG, ChNodeFEMxyz* nodeH) 
				{
					nodes[0]=nodeA; 
					nodes[1]=nodeB;
					nodes[2]=nodeC;
					nodes[3]=nodeD;
					nodes[4]=nodeE;
					nodes[5]=nodeF;
					nodes[6]=nodeG;
					nodes[7]=nodeH;
					std::vector<ChLcpVariables*> mvars;
					mvars.push_back(&nodes[0]->Variables());
					mvars.push_back(&nodes[1]->Variables());
					mvars.push_back(&nodes[2]->Variables());
					mvars.push_back(&nodes[3]->Variables());
					mvars.push_back(&nodes[4]->Variables());
					mvars.push_back(&nodes[5]->Variables());
					mvars.push_back(&nodes[6]->Variables());
					mvars.push_back(&nodes[7]->Variables());
					Kmatr.SetVariables(mvars);
				}
			

			//
			// QUADRATURE functions
			//

	virtual void SetDefaultIntegrationRule()
			{
				this->ir->SetIntOnCube(8, &this->GpVector);
			}

	virtual void SetReducedIntegrationRule()
			{
				this->ir->SetIntOnCube(1, &this->GpVector);
			}

	virtual void SetIntegrationRule(int nPoints)
			{
				this->ir->SetIntOnCube(nPoints, &this->GpVector);
			}

	
			//
			// FEM functions
			//
				
				/// Puts inside 'Jacobian' and 'J1' the Jacobian matrix and the shape functions derivatives matrix of the element.
				/// The vector "coord" contains the natural coordinates of the integration point.
				/// in case of hexahedral elements natural coords vary in the classical range -1 ... +1.
	virtual void ComputeJacobian(ChMatrixDynamic<>& Jacobian, ChMatrixDynamic<>& J1, ChVector<> coord) 
				{
					ChMatrixDynamic<> J2(8,3);

					J1.SetElement(0,0,-(1-coord.y)*(1-coord.z)/8);
					J1.SetElement(0,1,+(1-coord.y)*(1-coord.z)/8);
					J1.SetElement(0,2,+(1+coord.y)*(1-coord.z)/8);
					J1.SetElement(0,3,-(1+coord.y)*(1-coord.z)/8);
					J1.SetElement(0,4,-(1-coord.y)*(1+coord.z)/8);
					J1.SetElement(0,5,+(1-coord.y)*(1+coord.z)/8);
					J1.SetElement(0,6,+(1+coord.y)*(1+coord.z)/8);
					J1.SetElement(0,7,-(1+coord.y)*(1+coord.z)/8);

					J1.SetElement(1,0,-(1-coord.x)*(1-coord.z)/8);
					J1.SetElement(1,1,-(1+coord.x)*(1-coord.z)/8);
					J1.SetElement(1,2,+(1+coord.x)*(1-coord.z)/8);
					J1.SetElement(1,3,+(1-coord.x)*(1-coord.z)/8);
					J1.SetElement(1,4,-(1-coord.x)*(1+coord.z)/8);
					J1.SetElement(1,5,-(1+coord.x)*(1+coord.z)/8);
					J1.SetElement(1,6,+(1+coord.x)*(1+coord.z)/8);
					J1.SetElement(1,7,+(1-coord.x)*(1+coord.z)/8);

					J1.SetElement(2,0,-(1-coord.x)*(1-coord.y)/8);
					J1.SetElement(2,1,-(1+coord.x)*(1-coord.y)/8);
					J1.SetElement(2,2,-(1+coord.x)*(1+coord.y)/8);
					J1.SetElement(2,3,-(1-coord.x)*(1+coord.y)/8);
					J1.SetElement(2,4,+(1-coord.x)*(1-coord.y)/8);
					J1.SetElement(2,5,+(1+coord.x)*(1-coord.y)/8);
					J1.SetElement(2,6,+(1+coord.x)*(1+coord.y)/8);
					J1.SetElement(2,7,+(1-coord.x)*(1+coord.y)/8);

					J2.SetElement(0,0,nodes[0]->pos.x);
					J2.SetElement(1,0,nodes[1]->pos.x);
					J2.SetElement(2,0,nodes[2]->pos.x);
					J2.SetElement(3,0,nodes[3]->pos.x);
					J2.SetElement(4,0,nodes[4]->pos.x);
					J2.SetElement(5,0,nodes[5]->pos.x);
					J2.SetElement(6,0,nodes[6]->pos.x);
					J2.SetElement(7,0,nodes[7]->pos.x);
	
					J2.SetElement(0,1,nodes[0]->pos.y);
					J2.SetElement(1,1,nodes[1]->pos.y);
					J2.SetElement(2,1,nodes[2]->pos.y);
					J2.SetElement(3,1,nodes[3]->pos.y);
					J2.SetElement(4,1,nodes[4]->pos.y);
					J2.SetElement(5,1,nodes[5]->pos.y);
					J2.SetElement(6,1,nodes[6]->pos.y);
					J2.SetElement(7,1,nodes[7]->pos.y);

					J2.SetElement(0,2,nodes[0]->pos.z);
					J2.SetElement(1,2,nodes[1]->pos.z);
					J2.SetElement(2,2,nodes[2]->pos.z);
					J2.SetElement(3,2,nodes[3]->pos.z);
					J2.SetElement(4,2,nodes[4]->pos.z);
					J2.SetElement(5,2,nodes[5]->pos.z);
					J2.SetElement(6,2,nodes[6]->pos.z);
					J2.SetElement(7,2,nodes[7]->pos.z);

					Jacobian.MatrMultiply(J1,J2);				
				}

	
				/// Computes the matrix of partial derivatives and puts data in "GaussPt".
				///	Stores the determinant of the jacobian in "JacobianDet".
	virtual void ComputeMatrB(ChGaussPoint* GaussPt, double& JacobianDet) 
				{
					ChMatrixDynamic<> Jacobian(3,3);
					ChMatrixDynamic<> J1(3,8);
					ComputeJacobian(Jacobian, J1, (*GaussPt).GetLocalCoordinates());
				
					double Jdet=Jacobian.Det();
					JacobianDet = Jdet;		// !!! store the Jacobian Determinant: needed for the integration

					ChMatrixDynamic<> Jinv = Jacobian;
					Jinv.MatrInverse();

					ChMatrixDynamic<> Btemp(3,8);
					Btemp.MatrMultiply(Jinv,J1);
					GaussPt->MatrB->Resize(6,24);	// Remember to resize the matrix!

					GaussPt->MatrB->SetElement(0,0,Btemp(0,0));
					GaussPt->MatrB->SetElement(0,3,Btemp(0,1));
					GaussPt->MatrB->SetElement(0,6,Btemp(0,2));
					GaussPt->MatrB->SetElement(0,9,Btemp(0,3));
					GaussPt->MatrB->SetElement(0,12,Btemp(0,4));
					GaussPt->MatrB->SetElement(0,15,Btemp(0,5));
					GaussPt->MatrB->SetElement(0,18,Btemp(0,6));
					GaussPt->MatrB->SetElement(0,21,Btemp(0,7));

					GaussPt->MatrB->SetElement(1,1,Btemp(1,0));
					GaussPt->MatrB->SetElement(1,4,Btemp(1,1));
					GaussPt->MatrB->SetElement(1,7,Btemp(1,2));
					GaussPt->MatrB->SetElement(1,10,Btemp(1,3));
					GaussPt->MatrB->SetElement(1,13,Btemp(1,4));
					GaussPt->MatrB->SetElement(1,16,Btemp(1,5));
					GaussPt->MatrB->SetElement(1,19,Btemp(1,6));
					GaussPt->MatrB->SetElement(1,22,Btemp(1,7));

					GaussPt->MatrB->SetElement(2,2,Btemp(2,0));
					GaussPt->MatrB->SetElement(2,5,Btemp(2,1));
					GaussPt->MatrB->SetElement(2,8,Btemp(2,2));
					GaussPt->MatrB->SetElement(2,11,Btemp(2,3));
					GaussPt->MatrB->SetElement(2,14,Btemp(2,4));
					GaussPt->MatrB->SetElement(2,17,Btemp(2,5));
					GaussPt->MatrB->SetElement(2,20,Btemp(2,6));
					GaussPt->MatrB->SetElement(2,23,Btemp(2,7));

					GaussPt->MatrB->SetElement(3,0,Btemp(1,0));
					GaussPt->MatrB->SetElement(3,1,Btemp(0,0));
					GaussPt->MatrB->SetElement(3,3,Btemp(1,1));
					GaussPt->MatrB->SetElement(3,4,Btemp(0,1));
					GaussPt->MatrB->SetElement(3,6,Btemp(1,2));
					GaussPt->MatrB->SetElement(3,7,Btemp(0,2));
					GaussPt->MatrB->SetElement(3,9,Btemp(1,3));
					GaussPt->MatrB->SetElement(3,10,Btemp(0,3));
					GaussPt->MatrB->SetElement(3,12,Btemp(1,4));
					GaussPt->MatrB->SetElement(3,13,Btemp(0,4));
					GaussPt->MatrB->SetElement(3,15,Btemp(1,5));
					GaussPt->MatrB->SetElement(3,16,Btemp(0,5));
					GaussPt->MatrB->SetElement(3,18,Btemp(1,6));
					GaussPt->MatrB->SetElement(3,19,Btemp(0,6));
					GaussPt->MatrB->SetElement(3,21,Btemp(1,7));
					GaussPt->MatrB->SetElement(3,22,Btemp(0,7));

					GaussPt->MatrB->SetElement(4,1,Btemp(2,0));
					GaussPt->MatrB->SetElement(4,2,Btemp(1,0));
					GaussPt->MatrB->SetElement(4,4,Btemp(2,1));
					GaussPt->MatrB->SetElement(4,5,Btemp(1,1));
					GaussPt->MatrB->SetElement(4,7,Btemp(2,2));
					GaussPt->MatrB->SetElement(4,8,Btemp(1,2));
					GaussPt->MatrB->SetElement(4,10,Btemp(2,3));
					GaussPt->MatrB->SetElement(4,11,Btemp(1,3));
					GaussPt->MatrB->SetElement(4,13,Btemp(2,4));
					GaussPt->MatrB->SetElement(4,14,Btemp(1,4));
					GaussPt->MatrB->SetElement(4,16,Btemp(2,5));
					GaussPt->MatrB->SetElement(4,17,Btemp(1,5));
					GaussPt->MatrB->SetElement(4,19,Btemp(2,6));
					GaussPt->MatrB->SetElement(4,20,Btemp(1,6));
					GaussPt->MatrB->SetElement(4,22,Btemp(2,7));
					GaussPt->MatrB->SetElement(4,23,Btemp(1,7));

					GaussPt->MatrB->SetElement(5,0,Btemp(2,0));
					GaussPt->MatrB->SetElement(5,2,Btemp(0,0));
					GaussPt->MatrB->SetElement(5,3,Btemp(2,1));
					GaussPt->MatrB->SetElement(5,5,Btemp(0,1));
					GaussPt->MatrB->SetElement(5,6,Btemp(2,2));
					GaussPt->MatrB->SetElement(5,8,Btemp(0,2));
					GaussPt->MatrB->SetElement(5,9,Btemp(2,3));
					GaussPt->MatrB->SetElement(5,11,Btemp(0,3));
					GaussPt->MatrB->SetElement(5,12,Btemp(2,4));
					GaussPt->MatrB->SetElement(5,14,Btemp(0,4));
					GaussPt->MatrB->SetElement(5,15,Btemp(2,5));
					GaussPt->MatrB->SetElement(5,17,Btemp(0,5));
					GaussPt->MatrB->SetElement(5,18,Btemp(2,6));
					GaussPt->MatrB->SetElement(5,20,Btemp(0,6));
					GaussPt->MatrB->SetElement(5,21,Btemp(2,7));
					GaussPt->MatrB->SetElement(5,23,Btemp(0,7));

			}

				
				/// Computes the global STIFFNESS MATRIX of the element:    
				/// K = Volume * [B]' * [D] * [B]
				/// The number of Gauss Point is defined by SetIntegrationRule function (default: 8 Gp).
	virtual void ComputeStiffnessMatrix() 
		{
			double Jdet;
			ChMatrixDynamic<> *temp = new ChMatrixDynamic<>;
			ChMatrixDynamic<> BT;

			for(int i=0; i < GpVector.size(); i++)
			{
				ComputeMatrB(GpVector[i], Jdet);
				BT = *GpVector[i]->MatrB;
				BT.MatrTranspose();
				*temp = (BT * Material->Get_StressStrainMatrix() * *(GpVector[i]->MatrB));
				temp->MatrScale(GpVector[i]->GetWeight());
				temp->MatrScale(Jdet);
				StiffnessMatrix.MatrAdd(StiffnessMatrix,*temp);

			}
			delete temp;
		}


	virtual void SetupInitial() 
			{
				ComputeStiffnessMatrix();

			}

	virtual void GetStrain()
			{
						// Set up vector of nodal displacements
				ChMatrixDynamic<> displ(GetNcoords(),1);
				for(int i=0; i<GetNnodes(); i++)
					displ.PasteVector(this->nodes[i]->GetPos()-nodes[i]->GetX0(),i*3,0);
					
				for(int i=0; i<GpVector.size(); i++)
				{
					GpVector[i]->Strain.MatrMultiply((*GpVector[i]->MatrB), displ);
					delete GpVector[i]->MatrB;
				}
			}

	virtual void GetStress()
			{
				for(int i=0; i<GpVector.size(); i++)
				{
					GpVector[i]->Stress.MatrMultiply(Material->Get_StressStrainMatrix(), GpVector[i]->Strain);
				}
			}

				/// Sets H as the global stiffness matrix K, scaled  by Kfactor. Optionally, also
				/// superimposes global damping matrix R, scaled by Rfactor.
				/// (For the spring matrix there is no need to corotate local matrices: we already know a closed form expression.)
	virtual void ComputeKRmatricesGlobal	(ChMatrix<>& H, double Kfactor, double Rfactor=0) 
				{
					assert((H.GetRows() == 24) && (H.GetColumns()==24));

					// compute stiffness matrix (this is already the explicit
					// formulation of the corotational stiffness matrix in 3D)
					
						// calculate global stiffness matrix
					//SetupInitial(); // NO, we assume it has been computed at the beginning of the simulation
					ChMatrixDynamic<> tempMatr = StiffnessMatrix;
					tempMatr.MatrScale( Kfactor );

					H.PasteMatrix(&tempMatr,0,0);
				}

				/// Sets Hl as the local stiffness matrix K, scaled  by Kfactor. Optionally, also
				/// superimposes local damping matrix R, scaled by Rfactor.
				/// This is usually called only once in the simulation. 
	virtual void ComputeKRmatricesLocal (ChMatrix<>& Hl, double Kfactor, double Rfactor=0)
				{
					assert((Hl.GetRows() == 24) && (Hl.GetColumns() == 24));

					// to keep things short, here local K is as global K (anyway, only global K is used in simulations)
					ComputeKRmatricesLocal (Hl, Kfactor, Rfactor);
				}

				/// Computes the internal forces (ex. the actual position of
				/// nodes is not in relaxed reference position) and set values
				/// in the Fi vector.
	virtual void ComputeInternalForces	(ChMatrixDynamic<>& Fi)
				{
					assert((Fi.GetRows() == 24) && (Fi.GetColumns()==1));

						// set up vector of nodal displacements
					ChMatrixDynamic<> displ(24,1);
					displ.PasteVector(nodes[0]->pos - nodes[0]->GetX0(), 0, 0);
					displ.PasteVector(nodes[1]->pos - nodes[1]->GetX0(), 3, 0);
					displ.PasteVector(nodes[2]->pos - nodes[2]->GetX0(), 6, 0);
					displ.PasteVector(nodes[3]->pos - nodes[3]->GetX0(), 9, 0);
					displ.PasteVector(nodes[4]->pos - nodes[4]->GetX0(), 12, 0);
					displ.PasteVector(nodes[5]->pos - nodes[5]->GetX0(), 15, 0);
					displ.PasteVector(nodes[6]->pos - nodes[6]->GetX0(), 18, 0);
					displ.PasteVector(nodes[7]->pos - nodes[7]->GetX0(), 21, 0);

						// [Internal Forces] = [K] * [displ]
					Fi.MatrMultiply(StiffnessMatrix,displ);

				}

			//
			// Custom properties functions
			//

				/// Set the material of the element
	void   SetMaterial( ChSharedPtr<ChContinuumElastic> my_material) { Material = my_material; }
	ChSharedPtr<ChContinuumElastic> GetMaterial() {return Material;}

				/// Get the StiffnessMatrix
	ChMatrixDynamic<> GetStiffnessMatrix() {return StiffnessMatrix;}
				/// Get the Nth gauss point
	ChGaussPoint* GetGaussPoint(int N) {return GpVector[N];}


			//
			// Functions for interfacing to the LCP solver 
			//            (***not needed, thank to bookkeeping in parent class ChElementGeneric)




};

}//___end of namespace fem___
}//___end of namespace chrono___

#endif
