#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

#include "PluginLib.hpp"

PYBIND11_EMBEDDED_MODULE(PyPluginLib, m)
{
    m.doc() = "A Python API for the PluginLib library to allow users to make their own IA for the game";
    pybind11::class_<SP::PluginLib>(m, "PluginLib")
        .def(pybind11::init<std::string>())
        .def("Update", &SP::PluginLib::Update)
        .def("GetName", &SP::PluginLib::GetName)
        .def("GetRandomPawn", &SP::PluginLib::GetRandomPawn)
        .def("GetFirstPawn", &SP::PluginLib::GetFirstPawn)
        .def("SetAction", &SP::PluginLib::SetAction);
}