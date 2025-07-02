#include "PolarGridParameters.h"

#include <stdexcept>
#include <string>

#include <isce3/core/DateTime.h>
#include <isce3/core/LookSide.h>
#include <isce3/core/Linspace.h>

namespace py = pybind11;

using isce3::product::PolarGridParameters;
using isce3::core::DateTime;
using isce3::core::LookSide;

void addbinding(pybind11::class_<PolarGridParameters> & pyPolarGridParameters)
{
    pyPolarGridParameters
        .def(py::init<double, double, double, double, double, double, double, double, double, double,
             size_t, size_t, LookSide, size_t, size_t, DateTime>(),
                py::arg("sensing_start"),
                py::arg("wavelength"),
                py::arg("center_range"),
                py::arg("center_range_rate"),
                py::arg("polar_angle"),
                py::arg("polar_angle_rate"),
                py::arg("polar_aperture_scale_factor"),
                py::arg("polar_aperture_scale_factor_rate"),
                py::arg("range_pixel_spacing"),
                py::arg("azimuth_pixel_spacing"),
                py::arg("range_center_pixel"),
                py::arg("azimuth_center_pixel"),
                py::arg("lookside"),
                py::arg("length"),
                py::arg("width"),
                py::arg("ref_epoch"))
        .def(py::init([](double sensing_start,
                         double wavelength,
                         double center_range,
                         double center_range_rate,
                         double polar_angle,
                         double polar_angle_rate,
                         double polar_aperture_scale_factor,
                         double polar_aperture_scale_factor_rate,
                         double range_pixel_spacing,
                         double azimuth_pixel_spacing,
                         size_t range_center_pixel,
                         size_t azimuth_center_pixel,
                         const std::string& look_side,
                         size_t length,
                         size_t width,
                         const DateTime& ref_epoch) {

                    LookSide side = isce3::core::parseLookSide(look_side);

                    return PolarGridParameters(
                        sensing_start, wavelength, center_range, center_range_rate,
                        polar_angle, polar_angle_rate, polar_aperture_scale_factor,
                        polar_aperture_scale_factor_rate, range_pixel_spacing,
                        azimuth_pixel_spacing, range_center_pixel, azimuth_center_pixel,
                        side, length, width, ref_epoch);
                }),
                py::arg("sensing_start"),
                py::arg("wavelength"),
                py::arg("center_range"),
                py::arg("center_range_rate"),
                py::arg("polar_angle"),
                py::arg("polar_angle_rate"),
                py::arg("polar_aperture_scale_factor"),
                py::arg("polar_aperture_scale_factor_rate"),
                py::arg("range_pixel_spacing"),
                py::arg("azimuth_pixel_spacing"),
                py::arg("range_center_pixel"),
                py::arg("azimuth_center_pixel"),
                py::arg("look_side"),
                py::arg("length"),
                py::arg("width"),
                py::arg("ref_epoch"))
        .def_property_readonly("size", &PolarGridParameters::size)
        .def_property("sensing_start",
                py::overload_cast<>(&PolarGridParameters::sensingStart, py::const_),
                py::overload_cast<const double&>(&PolarGridParameters::sensingStart))
        .def_property("wavelength",
                py::overload_cast<>(&PolarGridParameters::wavelength, py::const_),
                py::overload_cast<const double&>(&PolarGridParameters::wavelength))
        .def_property("center_range",
                py::overload_cast<>(&PolarGridParameters::centerRange, py::const_),
                py::overload_cast<const double&>(&PolarGridParameters::centerRange))
        .def_property("center_range_rate",
                py::overload_cast<>(&PolarGridParameters::centerRangeRate, py::const_),
                py::overload_cast<const double&>(&PolarGridParameters::centerRangeRate))
        .def_property("polar_angle",
                py::overload_cast<>(&PolarGridParameters::polarAngle, py::const_),
                py::overload_cast<const double&>(&PolarGridParameters::polarAngle))
        .def_property("polar_angle_rate",
                py::overload_cast<>(&PolarGridParameters::polarAngleRate, py::const_),
                py::overload_cast<const double&>(&PolarGridParameters::polarAngleRate))
        .def_property("polar_aperture_scale_factor",
                py::overload_cast<>(&PolarGridParameters::polarApertureScaleFactor, py::const_),
                py::overload_cast<const double&>(&PolarGridParameters::polarApertureScaleFactor))
        .def_property("polar_aperture_scale_factor_rate",
                py::overload_cast<>(&PolarGridParameters::polarApertureScaleFactorRate, py::const_),
                py::overload_cast<const double&>(&PolarGridParameters::polarApertureScaleFactorRate))
        .def_property("range_pixel_spacing",
                py::overload_cast<>(&PolarGridParameters::rangePixelSpacing, py::const_),
                py::overload_cast<const double&>(&PolarGridParameters::rangePixelSpacing))
        .def_property("azimuth_pixel_spacing",
                py::overload_cast<>(&PolarGridParameters::azimuthPixelSpacing, py::const_),
                py::overload_cast<const double&>(&PolarGridParameters::azimuthPixelSpacing))
        .def_property("range_center_pixel",
                py::overload_cast<>(&PolarGridParameters::rangeCenterPixel, py::const_),
                py::overload_cast<const size_t&>(&PolarGridParameters::rangeCenterPixel))
        .def_property("azimuth_center_pixel",
                py::overload_cast<>(&PolarGridParameters::azimuthCenterPixel, py::const_),
                py::overload_cast<const size_t&>(&PolarGridParameters::azimuthCenterPixel))
        .def_property("lookside",
                py::overload_cast<>(&PolarGridParameters::lookSide, py::const_),
                py::overload_cast<LookSide>(&PolarGridParameters::lookSide))
        .def_property("width",
                py::overload_cast<>(&PolarGridParameters::width, py::const_),
                py::overload_cast<const size_t&>(&PolarGridParameters::width))
        .def_property("length",
                py::overload_cast<>(&PolarGridParameters::length, py::const_),
                py::overload_cast<const size_t&>(&PolarGridParameters::length))
        .def_property("ref_epoch",
                py::overload_cast<>(&PolarGridParameters::refEpoch, py::const_),
                py::overload_cast<const DateTime &>(&PolarGridParameters::refEpoch))
        .def("copy", [](const PolarGridParameters& self) {
                return PolarGridParameters(self);
        })
        .def_property_readonly("shape", [](const PolarGridParameters& self) {
                auto shape = py::tuple(2);
                shape[0] = self.length();
                shape[1] = self.width();
                return shape;
        })
        // FIXME Attribute names don't match ctor names.
        .def("__str__", [](const py::object self) {
                std::vector<std::string> keys {"sensing_start", "wavelength",
                        "center_range", "center_range_rate", "polar_angle",
                        "polar_angle_rate", "polar_aperture_scale_factor",
                        "polar_aperture_scale_factor_rate", "range_pixel_spacing",
                        "azimuth_pixel_spacing", "range_center_pixel",
                         "azimuth_center_pixel", "lookside", "length", "width", "ref_epoch"};
                std::string out("PolarGridParameters(");
                for (auto it = keys.begin(); it != keys.end(); ++it) {
                        auto key = *it;
                        auto ckey = key.c_str();
                        out += key + "=" + std::string(py::str(self.attr(ckey)));
                        if (it != keys.end() - 1)
                                out += ", ";
                }
                return out + ")";
        })
        ;
}
