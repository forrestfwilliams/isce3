#include "PolarGridParameters.h"


bool isce3::product::PolarGridParameters::
contains(const double azdist, const double srange) const {
    const auto minAzimuth = (azimuthCenterPixel() - length()) * azimuthPixelSpacing();
    // const auto halfAzimuthTimeInterval = azimuthPixelSpacing() / 2;
    // const auto halfRangePixelSpacing = rangePixelSpacing() / 2;
    // return aztime >= _sensingStart - halfAzimuthTimeInterval
    //         and srange >= _startingRange - halfRangePixelSpacing
    //         and aztime <= sensingStop() + halfAzimuthTimeInterval
    //         and srange <= endingRange() + halfRangePixelSpacing;
}
