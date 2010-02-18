//
/// \file
/// \ingroup math
/// \brief Several distributions with closed form density
//
#ifndef   __BINORMAL_QM_HPP__
#define   __BINORMAL_QM_HPP__
//
//
//#include <qmlib/math/SpecialFunctions.h>
#include <qmlib/math/distributions/simple.h>
//
//
//
QM_NAMESPACE2(math)  {


    class binormal_dist  {
    public:
    	binormal_dist(){}
    	virtual ~binormal_dist(){}
    	//
    	qm_real logdensity(qm_real x, qm_real y, qm_real rho);
    	qm_real density(qm_real x, qm_real y, qm_real rho)       {return this->logdensity(x,y,rho);}
    	//
    	/// \brief    Cumulative Bivariate Normal Distrubution Function
    	///
    	/// \f$ N(x) = \frac{1}/{\sqrt{2*\pi}}  \int_{-\infty}^z e^{-z*z/2} dz
    	///
    	/// This approximation produces values within six decimal places
    	qm_real cumulative(qm_real x, qm_real y, qm_real rho);
    	//
    	static qm_real Density(qm_real x, qm_real y, qm_real rho)     {BivariateNormalDist d; return d.density(x,y,rho);}
    	static qm_real Cumulative(qm_real x, qm_real y, qm_real rho)  {BivariateNormalDist d; return d.cumulative(x,y,rho);}
    	//static qm_real Icumulative(qm_real u) {BivariateNormalDist d; return d.icumulative(u);}
    private:
        qm_real k(qm_real x);
    };
    
    
    inline qm_real BivariateNormalDist::logdensity(qm_real x, qm_real y, qm_real rho)  {
            qm_real r2 = 1.0 - rho*rho;
            return -0.5*(x*x - 2.0*rho*x*y + y*y)/r2 - log(PI2*sqrt(r2));
        }
        
        
        
        inline qm_real BivariateNormalDist::cumulative(qm_real x, qm_real y, qm_real rho)  {
            static qm_real a[5] = {0.24840615, 0.39233107, 0.21141819, 0.03324666, 0.00082485334};
            static qm_real b[5] = {0.10024215, 0.48281397, 1.0609498,  1.7797294,  2.6697604};
            qm_real r2  = 1.0 - rho*rho;
            qm_real r2s = 1.0/sqrt(2.0*r2);
            qm_real x1  = x*r2s;
            qm_real y1  = y*r2s;
            if(x <= 0.0 && y <= 0.0 && rho <= 0)
            {
              qm_real sum = 0;
              for(qm_short i=0;i<5;i++)
                for(qm_short j=0;j<5;j++)
                  sum += a[i]*a[j]*exp(x1*(2*b[i] - x1) + y1*(2*b[j] - y1) + 2*rho*(b[i] - x1)*(b[j] - y1));
              return sqrt(r2)*sum/PI;
            }
            else if(x <= 0.0 && y >= 0.0 && rho >= 0)
              return NormalDist::Cumulative(x) - this->cumulative(x,-y,-rho);
            else if(x >= 0.0 && y <= 0.0 && rho >= 0)
              return NormalDist::Cumulative(y) - this->cumulative(-x,y,-rho);
            else if(x >= 0.0 && y >= 0.0 && rho <= 0)
              return NormalDist::Cumulative(x) + NormalDist::Cumulative(y) - 1 + this->cumulative(-x,-y,rho);
            else
            {
              qm_real den   = 1.0/sqrt(x*x -2*rho*x*y + y*y);
              qm_real rho1  = (rho*x - y)*sgn(x)*den;
              qm_real rho2  = (rho*y - x)*sgn(y)*den;
              qm_real delta = 0.25*(1 - sgn(x)*sgn(y));
              return BivariateNormalDist::cumulative(x,0,rho1) + this->cumulative(y,0,rho2) - delta;
            }
        }

        
}}

#endif	//	__BINORMAL_QM_HPP__


