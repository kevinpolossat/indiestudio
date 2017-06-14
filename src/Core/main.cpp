#include <boost/python.hpp>
#include <boost/filesystem.hpp>
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
	Py_Initialize();
	boost::filesystem::path workingDir = boost::filesystem::absolute("./src/BomberMan").normalize();
	PyObject* sysPath = PySys_GetObject((char *)"path");
	PyList_Insert(sysPath, 0, PyString_FromString(workingDir.string().c_str()));
    Game bomberman;

    return bomberman.run();
}
