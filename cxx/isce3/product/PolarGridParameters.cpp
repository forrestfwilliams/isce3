#include "PolarGridParameters.h"
#include "RadarGridProduct.h"

#include <isce3/core/Vector.h>
#include <isce3/core/Metadata.h>
#include <isce3/core/DateTime.h>

// TODO: this is a placeholder for now
isce3::product::PolarGridParameters::
PolarGridParameters(const RadarGridProduct & product, char frequency) :
    PolarGridParameters()
{
    validate();
}

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

void isce3::product::PolarGridParameters::
rangeRangeRate(double &rng, double &rngrate, const double azdist, const double rngdist) const {
    Eigen::Vector2d distInfo(rngdist - _rangeSceneCenter, azdist - _azimuthSceneCenter);
    Eigen::Vector2d rangeInfo = _polarMatrix * distInfo;
    rng = rangeInfo(0) + _centerRange;
    rngrate = rangeInfo(1) + _centerRangeRate;
}

double isce3::product::PolarGridParameters::
doppler(const double azdist, const double srange) const {
    double rng, rngrate;
    rangeRangeRate(rng, rngrate, azdist, srange);
    double doppler = -rngrate * 2 / 1.0;
    return doppler;
}
