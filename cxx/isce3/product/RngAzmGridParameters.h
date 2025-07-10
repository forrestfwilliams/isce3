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

/** Abstract class that all radar-space grids inherit from */
class isce3::product::RngAzmGridParameters {

    public:
        virtual void validate() const = 0;
        virtual size_t length() const = 0;
        virtual size_t width() const = 0;
        virtual double azimuthPixelSpacing() const = 0;
        virtual double azimuth(double) const = 0;
        virtual double azimuthIndex(double) const = 0;
        virtual double azimuthIndexPoint(double) const = 0;
        virtual double rangePixelSpacing() const = 0;
        virtual double slantRange(double) const = 0;
        virtual double slantRangeIndex(double) const = 0;
        virtual double slantRangeIndexPoint(double) const = 0;

        /** Virtual destructor */
        virtual ~RngAzmGridParameters() = default;

    // Protected data members can be accessed by derived classes
    protected:
        /** Sensing start time */
        double _sensingStart;

        /** Imaging wavelength */
        double _wavelength;

        /** Left or right looking geometry indicator */
        isce3::core::LookSide _lookSide;

        /** Number of lines in the image */
        size_t _rlength;

        /** Number of samples in the image */
        size_t _rwidth;

        /** Reference epoch for time tags */
        isce3::core::DateTime _refEpoch;
};
