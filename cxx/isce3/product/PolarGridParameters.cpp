#include "PolarGridParameters.h"


bool isce3::product::PolarGridParameters::
contains(const double azdist, const double srange) const {
    const double endingRange = (width() * rangePixelSpacing()) + rangeStart();
    const double endingAzimuth = (length() * azimuthPixelSpacing()) + azimuthStart();
    const double halfAzimuthTimeInterval = azimuthPixelSpacing() / 2;
    const double halfRangePixelSpacing = rangePixelSpacing() / 2;
    return azdist >= azimuthStart() - halfAzimuthTimeInterval
            and srange >= rangeStart() - halfRangePixelSpacing
            and azdist <= endingAzimuth + halfAzimuthTimeInterval
            and srange <= endingRange + halfRangePixelSpacing;
}
