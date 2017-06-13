#include <boost/python.hpp>
#include "Game.hh"
#include "IA.hh"

BOOST_PYTHON_MODULE(brain)
{
  boost::python::class_<IA>("IA")
		  .def("copyFromRefereeId", &IA::copyFromRefereeId)
		  .def("amIDeadFromId", &IA::amIDeadFromId)
		  .def("getNumberOfBoxesFromId", &IA::getNumberOfBoxesFromId)
		  .def("getNumberOfPlayerFromId", &IA::getNumberOfPlayerFromId)
		  .def("doActionFromId", &IA::doActionFromId)
		  .def("doUpdateFromId", &IA::doUpdateFromId)
          .def("getNumberOfPowerUpFromId", &IA::getNumberOfPowerUpFromId)
          .def("getMaxDepth", &IA::getMaxDepth)
          .def("isActionPossible", &IA::isActionPossible)
		  ;
}

int main(void) {
	PyImport_AppendInittab("brain", &initbrain);
	setenv("PYTHONPATH", "./src/BomberMan", 1);
	Py_Initialize();
	
	Game bomberman;
	return bomberman.run();
}
