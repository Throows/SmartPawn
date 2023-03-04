#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

#include "PluginLib.hpp"

PYBIND11_EMBEDDED_MODULE(PyPluginLib, m)
{
    m.doc() = "A Python API for the PluginLib library to allow users to make their own IA for the game";

    pybind11::enum_<MoveType>(m, "MoveType")
        .value("NONE", MoveType::NONE)
        .value("UP", MoveType::UP)
        .value("DOWN", MoveType::DOWN)
        .value("RIGHT", MoveType::RIGHT)
        .value("LEFT", MoveType::LEFT)
        .value("LEFT_TOP_CORNER", MoveType::LEFT_TOP_CORNER)
        .value("LEFT_DOWN_CORNER", MoveType::LEFT_DOWN_CORNER)
        .value("RIGHT_TOP_CORNER", MoveType::RIGHT_TOP_CORNER)
        .value("RIGHT_DOWN_CORNER", MoveType::RIGHT_DOWN_CORNER)
        .export_values();

    pybind11::class_<Coordinates>(m, "Coordinates")
        .def(pybind11::init<int, int>())
        .def_readonly("x", &Coordinates::x)
        .def_readonly("y", &Coordinates::y);

    pybind11::class_<PluginLib>(m, "PluginLib")
        .def(pybind11::init<std::string>())
        .def("GetMyRandomPawn", &PluginLib::GetMyRandomPawn)
        .def("GetEnnemyRandomPawn", &PluginLib::GetEnnemyRandomPawn)
        .def("GetEnnemyFirstPawn", &PluginLib::GetEnnemyFirstPawn)
        .def("GetMyFirstPawn", &PluginLib::GetMyFirstPawn)
        .def("SetAction", &PluginLib::SetAction)
        .def_property_readonly("name", &PluginLib::GetName)
        .def_readonly("myPawns", &PluginLib::myPawns)
        .def_readonly("ennemyPawns", &PluginLib::ennemyPawns)
        .def_property("pawnToMove", &PluginLib::GetPawnCoordinates, &PluginLib::SetPawnCoordinates);
}