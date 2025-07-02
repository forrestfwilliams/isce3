//-*- C++ -*-
//-*- coding: utf-8 -*-

#pragma once

#include <cmath>
#include "forward.h"

// isce3::core
#include <isce3/core/Metadata.h>
#include <isce3/core/DateTime.h>
#include <isce3/core/LookSide.h>
#include <isce3/core/TimeDelta.h>
#include <isce3/except/Error.h>

class isce3::product::PolarGridParameters {

    public:
        /** Default constructor */
        inline PolarGridParameters();

        /** Constructor from individual components and values. */
        inline PolarGridParameters(double sensingStart,
                                   double wavelength,
                                   double centerRange,
                                   double centerRangeRate,
                                   double polarAngle,
                                   double polarAngleRate,
                                   double polarApertureScaleFactor,
                                   double polarApertureScaleFactorRate,
                                   double rangePixelSpacing,
                                   double azimuthPixelSpacing,
                                   size_t rangeCenterPixel,
                                   size_t azimuthCenterPixel,
                                   isce3::core::LookSide lookSide,
                                   size_t length,
                                   size_t width,
                                   isce3::core::DateTime refEpoch);

        /** Copy constructor */
        inline PolarGridParameters(const PolarGridParameters & pgparam);

        /** Assignment operator */
        inline PolarGridParameters&
        operator=(const PolarGridParameters& pgparam);

        /** Get sensing start time in seconds since reference epoch */
        inline double sensingStart() const { return _sensingStart; }

        /** Set sensing start time in seconds since reference epoch */
        inline void sensingStart(const double & t){ _sensingStart = t; }

        /** Get radar wavelength in meters*/
        inline double wavelength() const { return _wavelength; }

        /** Set radar wavelength in meters*/
        inline void wavelength(const double & t) { _wavelength = t; }

        /** Get center slant range in meters*/
        inline double centerRange() const { return _centerRange; }

        /** Set center slant range in meters */
        inline void centerRange(const double & t) { _centerRange = t; }

        /** Get center slant range rate */
        inline double centerRangeRate() const { return _centerRangeRate; }

        /** Set center slant range rate */
        inline void centerRangeRate(const double & t) { _centerRangeRate = t; }

        /** Get polar angle of scene center */
        inline double polarAngle() const { return _polarAngle; }

        /** Get polar angle of scene center */
        inline void polarAngle(const double & t) { _polarAngle = t; }

        /** Get polar angle rate of scene center */
        inline double polarAngleRate() const { return _polarAngleRate; }

        /** Set polar angle rate of scene center */
        inline void polarAngleRate(const double & t) { _polarAngleRate = t; }

        /** Get polar aperture scale factor of scene center */
        inline double polarApertureScaleFactor() const { return _polarApertureScaleFactor; }

        /** Set polar aperture scale factor of scene center */
        inline void polarApertureScaleFactor(const double & t) { _polarApertureScaleFactor = t; }

        /** Get polar aperture scale factor rate of scene center */
        inline double polarApertureScaleFactorRate() const { return _polarApertureScaleFactorRate; }

        /** Set polar aperture scale factor of scene center */
        inline void polarApertureScaleFactorRate(const double & t) { _polarApertureScaleFactorRate = t; }

        /** Get slant range pixel spacing in meters*/
        inline double rangePixelSpacing() const { return _rangePixelSpacing; }

        /** Set slant range pixel spacing in meters */
        inline void rangePixelSpacing(const double & t) { _rangePixelSpacing = t; }

        /** Get azimuth pixel spacing in meters*/
        inline double azimuthPixelSpacing() const { return _azimuthPixelSpacing; }

        /** Set azimuth pixel spacing in meters */
        inline void azimuthPixelSpacing(const double & t) { _azimuthPixelSpacing = t; }

        /** Get center range pixel */
        inline size_t rangeCenterPixel() const { return _rangeCenterPixel; }

        /** Set center range pixel */
        inline void rangeCenterPixel(const size_t & t) { _rangeCenterPixel = t; }

        /** Get center azimuth pixel */
        inline size_t azimuthCenterPixel() const { return _azimuthCenterPixel; }

        /** Set center azimuth pixel */
        inline void azimuthCenterPixel(const size_t & t) { _azimuthCenterPixel = t; }

        /** Get the look direction */
        inline isce3::core::LookSide lookSide() const { return _lookSide; }

        /** Set look direction */
        inline void lookSide(isce3::core::LookSide side) { _lookSide = side; }

        /** Set look direction from a string */
        inline void lookSide(const std::string &);

        /** Get radar grid length */
        inline size_t length() const { return _rlength; }

        /** Set radar grid length */
        inline void length(const size_t & t) { _rlength = t; }

        /** Get radar grid width */
        inline size_t width() const { return _rwidth; }

        /** Set radar grid width */
        inline void width(const size_t & t) { _rwidth = t; }

        /** Get reference epoch DateTime*/
        inline const isce3::core::DateTime & refEpoch() const { return _refEpoch; }

        /** Set reference epoch DateTime
         *
         * Other dependent parameters like sensingStart are not modified. Use with caution.*/
        inline void refEpoch(const isce3::core::DateTime &epoch) { _refEpoch = epoch; }

        /** Get total number of radar grid elements */
        inline size_t size() const { return _rlength * _rwidth; }

    // Protected data members can be accessed by derived classes
    protected:
        /** Sensing start time */
        double _sensingStart;

        /** Imaging wavelength */
        double _wavelength;

        /** Range at center pixel */
        double _centerRange;

        /** Range rate at center pixel */
        double _centerRangeRate;

        /** Polar angle at center pixel */
        double _polarAngle;

        /** Polar angle rate at center pixel */
        double _polarAngleRate;

        /** Polar aperture scale factor at center pixel */
        double _polarApertureScaleFactor;

        /** Polar aperture scale factor rate at center pixel */
        double _polarApertureScaleFactorRate;

        /** Slant range pixel spacing */
        double _rangePixelSpacing;

        /** Azimuth pixel spacing */
        double _azimuthPixelSpacing;

        /** Center range pixel */
        size_t _rangeCenterPixel;

        /** Center azimuth pixel */
        size_t _azimuthCenterPixel;

        /** Left or right looking geometry indicator */
        isce3::core::LookSide _lookSide;

        /** Number of lines in the image */
        size_t _rlength;

        /** Number of samples in the image */
        size_t _rwidth;

        /** Reference epoch for time tags */
        isce3::core::DateTime _refEpoch;

        /** Validate parameters of data structure */
        inline void validate() const;
};

isce3::product::PolarGridParameters::PolarGridParameters()
    : _sensingStart {0}, _wavelength {0}, _centerRange {0}, _centerRangeRate {0},
      _polarAngle {0}, _polarAngleRate {0},
      _polarApertureScaleFactor {0}, _polarApertureScaleFactorRate {0},
      _rangePixelSpacing {0}, _azimuthPixelSpacing {0},
      _rangeCenterPixel {0}, _azimuthCenterPixel {0}, _lookSide(isce3::core::LookSide::Left),
      _rlength {0}, _rwidth {0}, _refEpoch {1} {}

// Copy constructors
/** @param[in] pgparam PolarGridParameters object */
isce3::product::PolarGridParameters::
PolarGridParameters(const PolarGridParameters & pgparams) :
    _sensingStart(pgparams.sensingStart()),
    _wavelength(pgparams.wavelength()),
    _centerRange(pgparams.centerRange()),
    _centerRangeRate(pgparams.centerRangeRate()),
    _polarAngle(pgparams.polarAngle()),
    _polarAngleRate(pgparams.polarAngleRate()),
    _polarApertureScaleFactor(pgparams.polarApertureScaleFactor()),
    _polarApertureScaleFactorRate(pgparams.polarApertureScaleFactorRate()),
    _rangePixelSpacing(pgparams.rangePixelSpacing()),
    _azimuthPixelSpacing(pgparams.azimuthPixelSpacing()),
    _rangeCenterPixel(pgparams.rangeCenterPixel()),
    _azimuthCenterPixel(pgparams.azimuthCenterPixel()),
    _lookSide(pgparams.lookSide()),
    _rlength(pgparams.length()),
    _rwidth(pgparams.width()),
    _refEpoch(pgparams.refEpoch()) { validate(); }

// Assignment operator
/** @param[in] pgparam PolarGridParameters object */
isce3::product::PolarGridParameters &
isce3::product::PolarGridParameters::
operator=(const isce3::product::PolarGridParameters & pgparams) {
    _sensingStart = pgparams.sensingStart();
    _wavelength = pgparams.wavelength();
    _centerRange = pgparams.centerRange();
    _centerRangeRate = pgparams.centerRangeRate();
    _polarAngle = pgparams.polarAngle();
    _polarAngleRate = pgparams.polarAngleRate();
    _polarApertureScaleFactor = pgparams.polarApertureScaleFactor();
    _polarApertureScaleFactorRate = pgparams.polarApertureScaleFactorRate();
    _rangePixelSpacing = pgparams.rangePixelSpacing();
    _azimuthPixelSpacing = pgparams.azimuthPixelSpacing();
    _rangeCenterPixel = pgparams.rangeCenterPixel();
    _azimuthCenterPixel = pgparams.azimuthCenterPixel();
    _lookSide = pgparams.lookSide();
    _rlength = pgparams.length();
    _rwidth = pgparams.width();
    _refEpoch = pgparams.refEpoch();
    validate();
    return *this;
}

// Constructor from individual components and values
isce3::product::PolarGridParameters::
PolarGridParameters(double sensingStart,
                    double wavelength,
                    double centerRange,
                    double centerRangeRate,
                    double polarAngle,
                    double polarAngleRate,
                    double polarApertureScaleFactor,
                    double polarApertureScaleFactorRate,
                    double rangePixelSpacing,
                    double azimuthPixelSpacing,
                    size_t rangeCenterPixel,
                    size_t azimuthCenterPixel,
                    isce3::core::LookSide lookSide,
                    size_t length,
                    size_t width,
                    isce3::core::DateTime refEpoch) :
    _sensingStart(sensingStart),
    _wavelength(wavelength),
    _centerRange(centerRange),
    _centerRangeRate(centerRangeRate),
    _polarAngle(polarAngle),
    _polarAngleRate(polarAngleRate),
    _polarApertureScaleFactor(polarApertureScaleFactor),
    _polarApertureScaleFactorRate(polarApertureScaleFactorRate),
    _rangePixelSpacing(rangePixelSpacing),
    _azimuthPixelSpacing(azimuthPixelSpacing),
    _rangeCenterPixel(rangeCenterPixel),
    _azimuthCenterPixel(azimuthCenterPixel),
    _lookSide(lookSide),
    _rlength(length),
    _rwidth(width),
    _refEpoch(refEpoch) { validate(); }

// Validation of radar grid parameters
void
isce3::product::PolarGridParameters::
validate() const
{

    std::string errstr = "";

    if (wavelength() <= 0.)
    {
        errstr += "Radar wavelength must be positive. \n";
    }

    if (rangePixelSpacing() <= 0. )
    {
        errstr += "Slant range pixel spacing must be positive. \n";
    }

    if (azimuthPixelSpacing() <= 0. )
    {
        errstr += "Azimuth pixel spacing must be positive. \n";
    }

    if (length() == 0)
    {
        errstr += "Radar Grid should have length of at least 1. \n";
    }

    if (width() == 0)
    {
        errstr += "Radar Grid should have width of at least 1. \n";
    }

    if (! errstr.empty())
    {
        throw isce3::except::InvalidArgument(ISCE_SRCINFO(), errstr);
    }
}


/** @param[in] look String representation of look side */
void
isce3::product::PolarGridParameters::
lookSide(const std::string & inputLook) {
    _lookSide = isce3::core::parseLookSide(inputLook);
}
