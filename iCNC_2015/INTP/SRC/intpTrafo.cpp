#include "stdafx.h"
#include "..\INC\INTP.h"
#include <math.h>
#define pi 3.14159265359
#define L 75 //晶圓取放機臂長(mm)



void trafoXYZtoUVW(INTP_DATA* intpDataPtr)
{
	intpDataPtr->newMKPos[2] = intpDataPtr->newRKPos[2];

	double X,Y;
	double sinU[2],sinV[2];
	double cosU[2],cosV[2];
	double U[2],V[2];
	double temp;
	double deltaU[2],deltaV[2];
	double deltaEnergy[2];

	X = intpDataPtr->newRKPos[0];
	Y = intpDataPtr->newRKPos[1];

	if((X == 0)&&( Y==0))  
	{
		intpDataPtr->newMKPos[0] = intpDataPtr->oldMKPos[0];
		intpDataPtr->newMKPos[1] = intpDataPtr->newMKPos[1]+180;

		if(intpDataPtr->newMKPos[1]>=360)
			intpDataPtr->newMKPos[1] = intpDataPtr->newMKPos[1]-360;
	}
	else if(X!=0)
	{
		temp = sqrt(4*X*X / (X*X + Y*Y) - (X*X)/(L*L));
		sinU[0] = 0.5 * ( Y/L + temp ); //sinU 的第一個解
		sinU[1] = 0.5 * ( Y/L - temp ); //sinU 的第二個解
		for(int i=0; i<2;i++)
		{
			sinV[i] = Y/L -sinU[i]; //用sinU解出sinV(對應兩組解)
			cosU[i] = (X*X +Y*Y)/(2*X*L) - Y*sinU[i]/X;
			cosV[i] = X/L - cosU[i];//用sinU解出cosU和cosV(對應兩組解)
		}
	}
	else 
	{
		temp = sqrt(4*Y*Y / (X*X + Y*Y) - (Y*Y)/(L*L));
		cosU[0] = 0.5*(X/L +temp); //sinU 的第一個解
		cosU[1] = 0.5*(X/L +temp); //sinU 的第二個解
		for(int i=0; i<2;i++)
		{
			cosV[i]=X/L - cosU[i];//用sinU解出sinV(對應兩組解)
			sinU[i] = (X*X + Y*Y)/(2*Y*L) - X*cosU[i]/Y;
			sinV[i] = Y/L - sinU[i];//用sinU解出cosU和cosV(對應兩組解)
		}//for(i<2)
	} //else (X==0)&&(Y!=0)
	/**************************************************
	        selct one of the solutions
	**************************************************/
	double Uu[2],Vv[2];

	for(int i=0;i<2;i++)
	{
		U[i] = thetaDegree(sinU[i], cosU[i]);//算出角度U(degree)
		V[i] = thetaDegree(sinV[i], cosV[i]);//算出角度V(degree)

		deltaU[i] = U[i] - intpDataPtr->oldMKPos[0];
		if(deltaU[i]<-180)
		{
			deltaU[i] = deltaU[i] + 360;
			U[i] = U[i] + 360;
		}
		else if(deltaU[i]>180)
		{
			deltaU[i] = U[i] - 360;
			U[i] = U[i] - 360;
		}


		deltaV[i] = V[i] - intpDataPtr->oldMKPos[1];
		if(deltaV[i]<-180)
		{
			deltaV[i] = V[i] + 360;
			V[i] = V[i] + 360;
		}
		else if(deltaV[i]>180)
		{
			deltaV[i] = V[i] - 360;
			V[i] = V[i] -360;
		}

		Uu[i] = deltaU[i];
		Vv[i] = deltaV[i];

		deltaEnergy[i] = (Uu[i]*Uu[i])+(Vv[i]*Vv[i]);

		//deltaEnergy[i] = (deltaU[i]*deltaU[i]) +　(deltaV[i]*deltaV[i]);
	                      // for算出兩組角度解分別與uvwOld差距的平方
	}
	if( deltaEnergy[0]<= deltaEnergy[1])
	{
		intpDataPtr->newMKPos[0] = U[0];
		intpDataPtr->newMKPos[1] = V[0];
	}//if第一組角度解deltaTheta較小
	else
	{
		intpDataPtr->newMKPos[0] = U[1];
		intpDataPtr->newMKPos[1] = V[1];
	}//else 第二組角度解deltaTheta較小
	return ;
} // trafoXYZtoUVW
void trafoUVWtoXYZ(INTP_DATA* intpDataPtr)
{
	double x,y,z;
	double u,v,w;
	u = intpDataPtr->decToIntpBlock.cordValue[0];
	v = intpDataPtr->decToIntpBlock.cordValue[1];
	w = intpDataPtr->decToIntpBlock.cordValue[2];

	x = 75*(cos(u*2*pi/360)+cos((u+v)*2*pi/360));
	y = 75*(sin(u*2*pi/360)+sin((u+v)*2*pi/360));
	z = w;

	intpDataPtr->decToIntpBlock.cordValue[0] = x;
	intpDataPtr->decToIntpBlock.cordValue[1] = y;
	intpDataPtr->decToIntpBlock.cordValue[2] = z;

	return ;
}
double thetaDegree(double sintheta, double costheta)
{
	double theta;

	if( (sintheta>0)&&(costheta>0))    //I
		theta = asin( sintheta )*180/pi;
	else if(( sintheta>0)&&(costheta<0))//II
		theta = asin(sintheta)*180/pi;
	else if((sintheta<0)&&(costheta<0))//III
		theta = 180 - asin( sintheta )*180/pi;
	else if((sintheta<0)&&(costheta>0))//IV
		theta = 360 + asin( sintheta )*180/pi;
	else if(sintheta ==0)    // X-axis  
	{
		if(costheta ==1)
			theta = 0;
		else 
			theta = 180;
	} // if sintheta ==0
	else                    // Y-axis
	{
		if(sintheta ==1)
			theta = 90;
		else
			theta =270;
	}//if costheta ==0


	return theta;
}//thetaDegree