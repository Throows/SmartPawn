#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

#include "PluginLib.hpp"

PYBIND11_EMBEDDED_MODULE(PyPluginLib, m)
{
    m.doc() = "A Python API for the PluginLib library to allow users to make their own IA for the game";
    
    pybind11::enum_<SP::MoveType>(m, "MoveType")
        .value("NONE", SP::MoveType::NONE)
        .value("UP", SP::MoveType::UP)
        .value("DOWN", SP::MoveType::DOWN)
        .value("RIGHT", SP::MoveType::RIGHT)
        .value("LEFT", SP::MoveType::LEFT)
        .value("LEFT_TOP_CORNER", SP::MoveType::LEFT_TOP_CORNER)
        .value("LEFT_DOWN_CORNER", SP::MoveType::LEFT_DOWN_CORNER)
        .value("RIGHT_TOP_CORNER", SP::MoveType::RIGHT_TOP_CORNER)
        .value("RIGHT_DOWN_CORNER", SP::MoveType::RIGHT_DOWN_CORNER)
        .export_values();

    pybind11::class_<SP::PluginLib>(m, "PluginLib")
        .def(pybind11::init<std::string>())
        .def("GetName", &SP::PluginLib::GetName)
        .def("GetRandomPawn", &SP::PluginLib::GetRandomPawn)
        .def("GetFirstPawn", &SP::PluginLib::GetFirstPawn)
        .def("SetAction", &SP::PluginLib::SetAction)
        .def("ValidateMove", &SP::PluginLib::ValidateMove)
        .def("Reset", &SP::PluginLib::Reset)
        .def("GetPawnMove", &SP::PluginLib::GetPawnMove)
        .def("GetPawnX", &SP::PluginLib::GetPawnX)
        .def("GetPawnY", &SP::PluginLib::GetPawnY);
}