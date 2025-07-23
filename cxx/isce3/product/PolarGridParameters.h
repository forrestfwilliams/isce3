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
#include <isce3/core/EMatrix.h>
#include <isce3/product/RngAzmGridParameters.h>

class isce3::product::PolarGridParameters : public RngAzmGridParameters {

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
                                   double rangeSceneCenter,
                                   double azimuthSceneCenter,
                                   double rangeStart,
                                   double azimuthStart,
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
        inline void polarAngle(const double & t) { _polarAngle = t; computePolarMatrix(); }

        /** Get polar angle rate of scene center */
        inline double polarAngleRate() const { return _polarAngleRate; }

        /** Set polar angle rate of scene center */
        inline void polarAngleRate(const double & t) { _polarAngleRate = t; computePolarMatrix(); }

        /** Get polar aperture scale factor of scene center */
        inline double polarApertureScaleFactor() const { return _polarApertureScaleFactor; }

        /** Set polar aperture scale factor of scene center */
        inline void polarApertureScaleFactor(const double & t) { _polarApertureScaleFactor = t; computePolarMatrix(); }

        /** Get polar aperture scale factor rate of scene center */
        inline double polarApertureScaleFactorRate() const { return _polarApertureScaleFactorRate; }

        /** Set polar aperture scale factor of scene center */
        inline void polarApertureScaleFactorRate(const double & t) { _polarApertureScaleFactorRate = t; computePolarMatrix(); }

        /** Get slant range pixel spacing in meters*/
        inline double rangePixelSpacing() const { return _rangePixelSpacing; }

        /** Set slant range pixel spacing in meters */
        inline void rangePixelSpacing(const double & t) { _rangePixelSpacing = t; }

        /** Get azimuth pixel spacing in meters*/
        inline double azimuthPixelSpacing() const { return _azimuthPixelSpacing; }

        /** Set azimuth pixel spacing in meters */
        inline void azimuthPixelSpacing(const double & t) { _azimuthPixelSpacing = t; }

        /** Get center range pixel */
        inline double rangeSceneCenter() const { return _rangeSceneCenter; }

        /** Set center range pixel */
        inline void rangeSceneCenter(const double & t) { _rangeSceneCenter = t; }

        /** Get center azimuth pixel */
        inline double azimuthSceneCenter() const { return _azimuthSceneCenter; }

        /** Set center azimuth pixel */
        inline void azimuthSceneCenter(const double & t) { _azimuthSceneCenter = t; }

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

        /** Get azimuth distance for a fractional line index */
        inline double azimuth(double line) const {
            return _azimuthStart + line * _azimuthPixelSpacing;
        }

        /** Get fractional line index for an azimuth distance */
        inline double azimuthIndex(double az_dist) const {
            return (az_dist - _azimuthStart) / _azimuthPixelSpacing;
        }

        /** Get fractional line index for an azimuth distance
         * assuming you start from the outer edge */
        inline double azimuthIndexPoint(double az_dist) const {
            return (az_dist - (_azimuthStart + 0.5 * _azimuthPixelSpacing)) / _azimuthPixelSpacing;
        }

        inline double azimuthMid() const {return _azimuthSceneCenter;}

        /** Get range distance for a fractional range index */
        inline double slantRange(double slant_range) const {
            return _rangeStart + slant_range * _rangePixelSpacing;
        }

        /** Get fractional range index for a range distance */
        inline double slantRangeIndex(double sr_dist) const {
            return (sr_dist - _rangeStart) / _rangePixelSpacing;
        }

        /** Get fractional range index for a range distance
         * assuming you start from the outer edge */
        inline double slantRangeIndexPoint(double sr_dist) const {
            return (sr_dist - (_rangeStart + 0.5 * _rangePixelSpacing)) / _rangePixelSpacing;
        }
        
        inline double slantRangeMid() const {return _centerRange;}


        inline double rangeStart() const {return _rangeStart;}
        inline void rangeStart(const double & t) { _rangeStart = t; }
        inline double startingRange() const {return _rangeStart;}
        inline double endingRange() const {return _rangeStart + (_rwidth * _rangePixelSpacing);}
        inline double midRange() const {return (endingRange() - startingRange()) / 2.0;}

        inline double azimuthStart() const {return _azimuthStart;}
        inline void azimuthStart(const double & t) { _azimuthStart = t; }

        /** Get the polar matrix */
        inline isce3::core::EMatrix2D<double, 2, 2> polarMatrix() const {return _polarMatrix;}

        /** Get inverse of polar matrix */
        inline isce3::core::EMatrix2D<double, 2, 2> polarMatrixInv() const {return _polarMatrixInv;}

        /** Crop/ Expand while keeping the spacing the same with top left offset and size */
        inline PolarGridParameters offsetAndResize(double yoff, double xoff, size_t ysize, size_t xsize) const
        {
            return PolarGridParameters( sensingStart(),
                                        wavelength(),
                                        centerRange(),
                                        centerRangeRate(),
                                        polarAngle(),
                                        polarAngleRate(),
                                        polarApertureScaleFactor(),
                                        polarApertureScaleFactorRate(),
                                        rangePixelSpacing(),
                                        azimuthPixelSpacing(),
                                        rangeSceneCenter() - xoff,
                                        azimuthSceneCenter() - yoff,
                                        rangeStart() + xoff,
                                        azimuthStart() + yoff,
                                        lookSide(),
                                        ysize,
                                        xsize,
                                        refEpoch());
        }

        /** Upsample */
        inline PolarGridParameters
        upsample(size_t az_upsampling_factor, size_t rg_upsampling_factor) const
        {
            // Check for number of points on edge
            if ((az_upsampling_factor  == 0) || (rg_upsampling_factor  == 0)) {
                std::string errstr = "Upsampling factor must be positive. " +
                                     std::to_string(az_upsampling_factor ) + "Az x" +
                                     std::to_string(rg_upsampling_factor ) +
                                     "Rg upsampling requested.";
                throw isce3::except::OutOfRange(ISCE_SRCINFO(), errstr);
            }

            // important: differently from multilook(), upsample does not
            // update _sensingStart or _startingRange
            return PolarGridParameters( sensingStart(),
                                        wavelength(),
                                        centerRange(),
                                        centerRangeRate(),
                                        polarAngle(),
                                        polarAngleRate(),
                                        polarApertureScaleFactor(),
                                        polarApertureScaleFactorRate(),
                                        rangePixelSpacing() / (1.0 * rg_upsampling_factor),
                                        azimuthPixelSpacing() / (1.0 * az_upsampling_factor),
                                        rangeSceneCenter(),
                                        azimuthSceneCenter(),
                                        rangeStart(),
                                        azimuthStart(),
                                        lookSide(),
                                        length() * az_upsampling_factor,
                                        width() * rg_upsampling_factor,
                                        refEpoch());
        }


        /*
         * Check if given az and slant range are within radargrid
         */
        bool contains(const double azdist, const double srange) const;

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
        double _rangeSceneCenter;

        /** Center azimuth pixel */
        double _azimuthSceneCenter;

        double _rangeStart;

        double _azimuthStart;

        /** Left or right looking geometry indicator */
        isce3::core::LookSide _lookSide;

        /** Number of lines in the image */
        size_t _rlength;

        /** Number of samples in the image */
        size_t _rwidth;

        /** Reference epoch for time tags */
        isce3::core::DateTime _refEpoch;

        /** Polar angle range and range rate conversion matrix */
        isce3::core::EMatrix2D<double, 2, 2> _polarMatrix;

        /** Polar angle range and range rate conversion matrix */
        isce3::core::EMatrix2D<double, 2, 2> _polarMatrixInv;

        /** Compute the polar matrix terms based on polar angle and polar aperture scale factor */
        inline void computePolarMatrix();

        /** Validate parameters of data structure */
        inline void validate() const;
};

isce3::product::PolarGridParameters::PolarGridParameters()
    : _sensingStart {0}, _wavelength {0}, _centerRange {0}, _centerRangeRate {0},
      _polarAngle {0}, _polarAngleRate {0},
      _polarApertureScaleFactor {0}, _polarApertureScaleFactorRate {0},
      _rangePixelSpacing {0}, _azimuthPixelSpacing {0},
      _rangeSceneCenter {0}, _azimuthSceneCenter {0},
      _rangeStart {0}, _azimuthStart {0},
      _lookSide(isce3::core::LookSide::Left), _rlength {0}, _rwidth {0}, _refEpoch {1} {}

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
    _rangeSceneCenter(pgparams.rangeSceneCenter()),
    _azimuthSceneCenter(pgparams.azimuthSceneCenter()),
    _rangeStart(pgparams.rangeStart()),
    _azimuthStart(pgparams.azimuthStart()),
    _lookSide(pgparams.lookSide()),
    _rlength(pgparams.length()),
    _rwidth(pgparams.width()),
    _refEpoch(pgparams.refEpoch()) { computePolarMatrix(); validate(); }

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
    _rangeSceneCenter = pgparams.rangeSceneCenter();
    _azimuthSceneCenter = pgparams.azimuthSceneCenter();
    _rangeStart = pgparams.rangeStart();
    _azimuthStart = pgparams.azimuthStart();
    _lookSide = pgparams.lookSide();
    _rlength = pgparams.length();
    _rwidth = pgparams.width();
    _refEpoch = pgparams.refEpoch();
    computePolarMatrix();
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
                    double rangeSceneCenter,
                    double azimuthSceneCenter,
                    double rangeStart,
                    double azimuthStart,
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
    _rangeSceneCenter(rangeSceneCenter),
    _azimuthSceneCenter(azimuthSceneCenter),
    _rangeStart(rangeStart),
    _azimuthStart(azimuthStart),
    _lookSide(lookSide),
    _rlength(length),
    _rwidth(width),
    _refEpoch(refEpoch) { computePolarMatrix(); validate(); }

// Compute the polar matrix terms based on polar angle and polar aperture scale factor
void
isce3::product::PolarGridParameters::computePolarMatrix()
{
    const double theta = _polarAngle;
    const double ksf = _polarApertureScaleFactor;
    const double dksf_dtheta = _polarApertureScaleFactorRate;
    const double dtheta_dt = _polarAngleRate;

    const double cos_polar = std::cos(theta);
    const double sin_polar = std::sin(theta);

    _polarMatrix(0,0) = ksf * cos_polar;
    _polarMatrix(0,1) = ksf * sin_polar;
    _polarMatrix(1,0) = (dksf_dtheta * cos_polar - ksf * sin_polar) * dtheta_dt;
    _polarMatrix(1,1) = (dksf_dtheta * sin_polar + ksf * cos_polar) * dtheta_dt;
    _polarMatrixInv = _polarMatrix.inverse();
}

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
