

//
/// \file
/// \ingroup python
/// \brief Exposes to Python the PDE library

#include <qmlib/python/pyconfig.hpp>

//#include <qmlib/math/pde/models/lrcd.hpp>
//#include <qmlib/python/pde_wrap.hpp>




QM_NAMESPACE2(python)

void pde_wrap()  {
/*	
	using namespace boost::python;
    QM_USING_NAMESPACE2(math);
    
    enum_<timeschemes>("timeschemes")
    	.value("euler",			_euler)
        .value("henn",			_henn)
        .value("trapezoidal",	_trapezoidal)
        .export_values()
        ;
    
    typedef structured_grid<1> grid1d;
    typedef structured_grid<2> grid2d;
    typedef pde_coefficient<1u,qm_real> pde_coefficient_1d;
    typedef QM_SMART_PTR(pde_coefficient_1d) PDEC1D;
    register_ptr_to_python<PDEC1D>();
    register_ptr_to_python<GRID1D>();
    register_ptr_to_python<GRID2D>();
    
    return_value_policy<copy_const_reference> ccr;
    return_value_policy<copy_non_const_reference> cncr;
    
    
    // Export PDE operators
    export_pde_operator<first_centered<qm_real,1,1,2> >("FCD1D","First central difference operator for 1D grids. Secon Order accurate");
    export_pde_operator<second_centered<qm_real,1,1,2> >("SCD1D","Second central difference operator for 1D grids. Secon Order accurate");
    
    // Export base classes for PDE models
    export_pde_model<qm_real,1u>("pdemodel_1d","Base class for 1D pde solutions on real numbers");
    export_pde_model<qm_real,2u>("pdemodel_2d","Base class for 2D pde solutions on real numbers");
    
    class_<time_marching_result>("time_marching_result","Few informations regarding a time marching calculation",no_init)
    	.def("__str__",						&time_marching_result::tostring)
    	.def("__repr__",					&time_marching_result::tostring)
    	.add_property("steps",  			&time_marching_result::steps,"Number of time steps performed")
    	.add_property("dt", 				&time_marching_result::dt,"Time step used")
    	.add_property("cfl", 				&time_marching_result::cfl,"The cfl number used in the calculation")
    	.add_property("time", 				&time_marching_result::time,"Total time")
    	.add_property("performance", 		&time_marching_result::performance,"Time taken for calculation")
    	;
    
    class_<gridN>("grid", "base class for space discretization", no_init)
    	.def("__str__",						&gridN::tostring)
    	.def("__repr__",					&gridN::tostring)
    	.def("__len__",						&gridN::points,"Total number of points")
    	.def("volume",						&gridN::volume,"Volume associated with a point i")
    	.add_property("points",				&gridN::points,"Total number of points")
      	.add_property("minvolume",          &gridN::minvolume, "The smalles cell size in the grid")
      	.add_property("dimensions",		    &gridN::dimensions, "Number of spacial dimensions")
      	;
      
    class_<structured_grid<1>, bases<gridN> >("grid_1d","One dimensional PDE grid", no_init)
    	.def("point", 			make_function(&structured_grid<1>::point,ccr),"Point coordinates")
    	.def("npoints",			&structured_grid<1>::npoints,"Points in one direction")
    	.def("coors",			&structured_grid<1>::coors<qm_list>)
        ;
    
    class_<structured_grid<2>, bases<gridN> >("grid_2d","Two dimensional orthogonal strcutured PDE grid",no_init)
    	.def("point", 			make_function(&structured_grid<2>::point,ccr),"Point coordinates")
    	.def("npoints",			&structured_grid<2>::npoints,"Number of points in one direction")
    	.def("coors",			&structured_grid<2>::coors<qm_list>)
        ;
    
    //_____________________________________________________________________
    // PDE model
    
    class_<pde_coefficient_wrapper<1u,qm_real>, boost::noncopyable, bases<basedes> >("pdecoef1d",
    		"General pde coefficient for 1d grids")
    	.def("eval",			&pde_coefficient_1d::eval)
    	.add_property("grid",	&pde_coefficient_1d::get_grid)
    	.add_property("grid",	make_function(&pde_coefficient_1d::get_timegrid,ccr))
    	;
    
    typedef ReacConvDiff<qm_real,1u,true> linearReacConvDiff1D;
    class_<linearReacConvDiff1D, bases<pdemodel_base<qm_real,1u> > >("rcdmodel1d",
    	"The 1D linear reaction convection diffusion equation\n V_t = c(t,x) V_x + d(t,x) V_xx + r(t,x) V",
    	init<GRID1D,PDEC1D,PDEC1D,PDEC1D>())
    	.def(init<GRID1D,qm_real,qm_real,qm_real>())
    	.def("lhs",							make_function(&linearReacConvDiff1D::lhs,cncr),"Left hand side matrix")
    	.add_property("diffobj",			make_function(&linearReacConvDiff1D::diffusion,ccr),"The diffusion coefficient object")
    	.add_property("convobj",			make_function(&linearReacConvDiff1D::convection,ccr),"The convection coefficient object")
		.add_property("reacobj",			make_function(&linearReacConvDiff1D::reaction,ccr),"The reaction coefficient object")
		.def("diffusion",					&linearReacConvDiff1D::get_diffusion,"Evaluate diffusion coefficients on the grid")
		.def("convection",					&linearReacConvDiff1D::get_convection,"Evaluate convection coefficients on the grid")
		.def("reaction",					&linearReacConvDiff1D::get_reaction,"Evaluate reaction coefficients on the grid")
     	;
    //______________________________________________________________________
    
    
    def("grid1d", &structured_grid_factory<1>::make0, "Generate a 1D grid for PDE solution");
    def("grid1d", &structured_grid_factory<1>::make1, "Generate a 1D grid for PDE solution");
    def("grid2d", &structured_grid_factory<2>::make0, "Generate a 2D grid for PDE solution");
    def("grid2d", &structured_grid_factory<2>::make1, "Generate a 2D grid for PDE solution");
    def("grid2d", &structured_grid_factory<2>::make2, "Generate a 2D grid for PDE solution");
    def("trapezoidal", &time_marching::advance<_trapezoidal,linearReacConvDiff1D>);
	*/
}


QM_NAMESPACE_END2;


