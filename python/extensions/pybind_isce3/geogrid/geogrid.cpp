#include "geogrid.h"
#include "getRadarGrid.h"
#include "relocateRaster.h"
#include <isce3/product/RadarGridParameters.h>
#include <isce3/product/PolarGridParameters.h>

void addsubmodule_geogrid(py::module & m)
{
    py::module m_geogrid = m.def_submodule("geogrid");

    addbinding_get_radar_grid<isce3::product::RadarGridParameters>(m_geogrid);
    addbinding_get_radar_grid<isce3::product::PolarGridParameters>(m_geogrid);
    addbinding_relocate_raster(m_geogrid);
}
