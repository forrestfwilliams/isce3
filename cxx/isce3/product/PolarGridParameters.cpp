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

double isce3::product::PolarGridParameters::
doppler(const double azdist, const double srange) const {
    double rel_azdist = azdist - _azimuthSceneCenter;
    double rel_range = srange - _rangeSceneCenter;
    double range_rate = rel_range * _polarMatrix(1,0) + rel_azdist * _polarMatrix(1, 1);
    double doppler = -range_rate * 2 / _wavelength;
    return doppler;
}
