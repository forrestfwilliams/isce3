#pragma once

#include <isce3/product/PolarGridParameters.h>
#include <pybind11/pybind11.h>

void addbinding(pybind11::class_<isce3::product::PolarGridParameters> &);
