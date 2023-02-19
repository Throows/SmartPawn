#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

#include "PluginLib.hpp"

#define PYBIND11_DETAILED_ERROR_MESSAGES 1

PYBIND11_EMBEDDED_MODULE(PyPluginLib, m)
{
    m.doc() = "A Python API for the PluginLib library to allow users to make their own IA for the game";

    pybind11::class_<PluginLib>(m, "PluginLib")
        .def(pybind11::init<std::string>())
        .def("GetRandomPawn", &PluginLib::GetRandomPawn)
        .def("GetFirstPawn", &PluginLib::GetFirstPawn)
        .def("SetAction", &PluginLib::SetAction)
        .def("Reset", &PluginLib::Reset)
        .def_property_readonly("name", &PluginLib::GetName)
        .def_property_readonly("hasPlayed", &PluginLib::ValidateMove)
        .def_property_readonly("pawnX", &PluginLib::GetPawnX)
        .def_property_readonly("pawnY", &PluginLib::GetPawnY)
        .def_property_readonly("moveType", &PluginLib::GetPawnMove);
}