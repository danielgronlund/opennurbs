//
// Copyright (c) 1993-2022 Robert McNeel & Associates. All rights reserved.
// OpenNURBS, Rhinoceros, and Rhino3D are registered trademarks of Robert
// McNeel & Associates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//
// For complete openNURBS copyright information see <http://www.opennurbs.org>.
//
////////////////////////////////////////////////////////////////

#if !defined(ON_SUN_INC_)
#define ON_SUN_INC_

// Class ON_SunEngine is a sun calculation engine. It's responsible for doing the astronomical calculations
// used by the sun. Note that most ON_Sun methods don't use this class. Only the utility methods use
// this because generally, ON_Sun is a simple sun object that merely gets and sets stored values.
// If you want to do sun calculations with OpenNURBS you should use this class or ON_SunEx instead of ON_Sun.

class ON_CLASS ON_SunEngine
{
public:
  enum class Accuracy
  {
    Minimum, // Suitable for doing many calculations when you just need rough results quickly.
    Maximum, // Suitable for generating accurate tables of sun positions (e.g., an ephemeris).
  };

  ON_SunEngine(Accuracy a = Accuracy::Minimum);
  ON_SunEngine(const ON_SunEngine&);
  virtual ~ON_SunEngine();

  const ON_SunEngine& operator = (const ON_SunEngine&);

  bool operator == (const ON_SunEngine& e);
  bool operator != (const ON_SunEngine& e);

  // Return the latitude of the observer in degrees.
  virtual double Latitude(void) const;

  // Return the longitude of the observer in degrees.
  virtual double Longitude(void) const;

  // Set the latitude of the observer in degrees. Must be in the range -90 to +90.
  // This value is used by the calculation of the sun's azimuth and altitude.
  // Returns true if latitude is valid, else false.
  virtual bool SetLatitude(double dLat);

  // Set the longitude of the observer in degrees. Must be in the range -180 to +180.
  // This value is used by the calculation of the sun's azimuth and altitude.
  // Returns true if longitude is valid, else false.
  virtual bool SetLongitude(double dLong);

  // Set the time zone of the observer in hours. Must be in the range -12 to +13.
  // Returns true if hours is valid, else false.
  virtual bool SetTimeZoneHours(double dHours);

  // Set the daylight saving of the observer in minutes. Must be in the range 0 to 120.
  // Returns true if minutes is valid, else false.
  virtual bool SetDaylightSavingMinutes(int iMinutes);

  // Set the local date and time of the observer. The date must lie between 1800 and 2199 inclusive.
  // The time is supplied as decimal hours which must be in the range 0 to 24.
  // Returns true if date and time are valid, else false.
  virtual bool SetLocalDateTime(int iYear, int iMonth, int iDay, double dHours);

  // Set the local Julian Day of the observer. Optional alternative to calling SetLocalDateTime().
  // Returns true if Julian Day is valid, else false.
  virtual bool SetLocalJulianDay(double dLocalJulianDay);

  // Returns The azimuth of the sun in degrees.
  virtual double Azimuth(void) const;

  // Returns The altitude of the sun in degrees.
  virtual double Altitude(void) const;

  // Returns The Julian Day corresponding to Universal Time (UT ~ GMT).
  virtual double JulianDay(void) const;

  // Returns The Julian Day corresponding to local time.
  virtual double LocalJulianDay(void) const;

  // Returns The time zone of the observer in hours.
  virtual double TimeZoneHours(void) const;

  // Returns The daylight saving of the observer in minutes.
  virtual int DaylightSavingMinutes(void) const;

  // Gets the local date and time of the observer.
  // Param year accepts the year in the range 1800 to 2199.
  // Param month accepts the month in the range 1 to 12.
  // Param day accepts the day in the range 1 to 31.
  // Param hours accepts the hour in the range 0 to 24.
  virtual void LocalDateTime(int& year, int& month, int& day, double& hours) const;

  // Helper function; returns the number of days in a month for a specific year.
  static int DaysInMonth(int month, int year);

  // Helper function; converts azimuth and altitude to unit vector.
  static void ConvertHorizonCoordsToSolarVector(double dAzimuth, double dAltitude, double* dVector);

  // Helper function; converts unit vector to azimuth and altitude.
  static void ConvertSolarVectorToHorizonCoords(const double* dVector, double& dAzimuth, double& dAltitude);

private:
  class CImpl;
  CImpl* _impl;
};

// Class ON_Sun represents a 'sun'. Note that generally it does not perform any astronomical calculations;
// it merely allows the programmer to get and set the various sun properties. Only the utility methods
// at the end of the class perform calculations (by using ON_SunEngine). If you want to do general sun
// calculations with OpenNURBS you should use ON_SunEngine or ON_SunEx instead of this class.

class ON_CLASS ON_Sun
{
public:
  ON_Sun();
  ON_Sun(ON_XMLNode& model_node);
  ON_Sun(const ON_Sun& sun);
  virtual ~ON_Sun();

  // Returns the minimum allowed year for sun methods.
  static int MinYear(void);

  // Returns the maximum allowed year for sun methods.
  static int MaxYear(void);

  virtual const ON_Sun& operator = (const ON_Sun& sun);

  virtual bool operator == (const ON_Sun& sun) const;
  virtual bool operator != (const ON_Sun& sun) const;

  // Returns true if enabling/disabling the sun is allowed, else false.
  virtual bool EnableAllowed(void) const;

  // Returns true if the sun is enabled, else false.
  virtual bool EnableOn(void) const;

  // Returns true if manual control of the sun position is allowed, else false.
  virtual bool ManualControlAllowed(void) const;

  // Returns true if manual control of the sun position is in effect, else false.
  virtual bool ManualControlOn(void) const;

  // Returns The world angle corresponding to North in degrees.
  // This angle is zero along the x-axis and increases anticlockwise.
  virtual double North(void) const;

  // Returns the azimuth of the sun in degrees. The value increases Eastwards with North as zero.
  // Note: This value is not affected by the direction of north. See North().
  virtual double Azimuth(void) const;

  // Returns the altitude of the sun in degrees.
  virtual double Altitude(void) const;

  // Returns the latitude of the observer.
  virtual double Latitude(void) const;

  // Returns the longitude of the observer.
  virtual double Longitude(void) const;

  // Returns the time zone of the observer in decimal hours.
  virtual double TimeZone(void) const;

  // Returns true if daylight saving is on, else false.
  virtual bool DaylightSavingOn(void) const;

  // Returns the daylight saving offset of the observer in minutes.
  virtual int DaylightSavingMinutes(void) const;

  // Retrieves the local date and time of the observer.
  // Param year accepts the year in the range MinYear() to MaxYear().
  // Param month accepts the month in the range 1 to 12.
  // Param day accepts the day in the range 1 to 31.
  // Param hours accepts the time expressed as decimal hours in the range 0 to 24.
  // Returns The local date and time of the observer.
  virtual void LocalDateTime(int& year, int& month, int& day, double& hours) const;

  // Returns the intensity to be used for the sun. This is 1.0 by default.
  virtual double Intensity(void) const;

  // Returns the shadow intensity to be used for the sun. This is 1.0 by default. 0.0 turns off all shadows.
  virtual double ShadowIntensity(void) const;

  // Set whether or not enabling/disabling the sun is allowed.
  virtual void SetEnableAllowed(bool allowed);

  // Set whether or not the sun is enabled.
  virtual void SetEnableOn(bool on);

  // Set whether or not manual control of the sun position is allowed.
  virtual void SetManualControlAllowed(bool allowed);

  // Set whether or not manual control of the sun position is in effect.
  virtual void SetManualControlOn(bool manual);

  // Set the azimuth corresponding to North.
  // north is the world angle corresponding to North in degrees in the range 0 to 360.
  // This angle is zero along the x-axis and increases anticlockwise.
  virtual void SetNorth(double north);

  // Set the azimuth of the sun when manual control is in effect.
  // Param azimuth is the sun's azimuth in degrees. The value increases Eastwards with North as zero.
  // Note: This value is not affected by the direction of north.
  virtual void SetAzimuth(double azimuth);

  // Set the sun's altitude when manual control is in effect.
  // Param altitude is the sun's altitude in degrees in the range -90 to +90.
  virtual void SetAltitude(double altitude);

  // Set the latitude of the observer.
  // Param latitude is the observer's latitude in degrees in the range -90 to +90.
  virtual void SetLatitude(double latitude);

  // Set the longitude of the observer.
  // Param longitude is the observer's longitude in degrees in the range -180 to +180.
  virtual void SetLongitude(double longitude);

  // Set the time zone of the observer in hours, in the range -12 to +13.
  virtual void SetTimeZone(double hours);

  // Set whether or not the observer is using daylight saving time.
  virtual void SetDaylightSavingOn(bool on);

  // Set the daylight saving of the observer in minutes, in the range 0 to 120.
  virtual void SetDaylightSavingMinutes(int minutes);

  // Set the local date and time of the observer.
  // Param year is the year which must lie between MinYear() to MaxYear() inclusive.
  // Param month is the month in the range 1 to 12.
  // Param day is the day in the range 1 to 31.
  // Param hours is the time expressed as decimal hours in the range 0 to 24.
  // Returns true if successful, false if the date is out of range.
  virtual bool SetLocalDateTime(int year, int month, int day, double hours);

  // Set the shadow intensity to be used for the sun. This is 1.0 by default. 0.0 turns off all shadows.
  virtual void SetShadowIntensity(double intensity);

  // Set the intensity to be used for the sun.  This is 1.0 by default.
  virtual void SetIntensity(double intensity);

  // Returns the CRC of the sun state.
  virtual ON__UINT32 DataCRC(ON__UINT32 current_remainder) const;

  // Returns true if all the sun parameters are valid, or false if any value is invalid.
  virtual bool IsValid(void) const;

  // Load the sun properties from a 'sun' XML node.
	virtual void LoadFromXMLNode(const ON_XMLNode& node);

  // Save the sun properties to a 'sun' XML node.
	virtual void SaveToXMLNode(ON_XMLNode& node) const;

  // Emergency virtual function for future expansion.
  virtual void* EVF(const wchar_t* func, void* data);

public: // These utility methods are provided for convenience and perform calculations by using ON_SunEngine.

  // Get an ON_Light which represents the sun. Note that this does not actually calculate the sun's
  // azimuth or altitude from the place and time. It merely uses the stored azimuth and altitude values.
  virtual ON_Light Light(void) const;

  // Retrieves the date and time of the observer expressed in Coordinated Universal Time. This is the same
  // as the local date and time adjusted for the observer's time zone and daylight saving.
  // Param year accepts the year in the range MinYear() to MaxYear().
  // Param month accepts the month in the range 1 to 12.
  // Param day accepts the day in the range 1 to 31.
  // Param hours accepts the time expressed as decimal hours in the range 0 to 24.
  // Returns The UTC date and time of the observer.
  virtual void UTCDateTime(int& year, int& month, int& day, double& hours) const;

  // Set the date and time of the observer expressed in Coordinated Universal Time. This is the same
  // as the local date and time adjusted for the observer's time zone and daylight saving.
  // Param year is the year which must lie between MinYear() to MaxYear() inclusive.
  // Param month is the month in the range 1 to 12.
  // Param day is the day in the range 1 to 31.
  // Param hours is the time expressed as decimal hours in the range 0 to 24.
  // Returns true if successful, false if the date is out of range.
  virtual bool SetUTCDateTime(int year, int month, int day, double hours);

  // Returns The sun's direction vector in world space, taking into account the sun's azimuth and
  // altitude and the direction of north. Note that this does not actually calculate the azimuth or
  // altitude from the place and time; it merely uses the stored azimuth and altitude values.
  virtual ON_3dVector CalculateVectorFromAzimuthAndAltitude(void) const;

  // Calculates and sets the sun's azimuth and altitude taking into account the direction of north.
  virtual void SetAzimuthAndAltitudeFromVector(const ON_3dVector& v);

  // Get a color for rendering a sun light when the sun is at a particular altitude in the sky.
  static ON_4fColor SunColorFromAltitude(double altitude);

  // Returns true if the specified time is within the range supported by ON_Sun.
  static bool IsValidDateTime(int year, int month, int day, int hour, int min, int sec);

private:
  // For internal use only.
  friend class ON_3dmRenderSettingsPrivate;
  void SetXMLNode(ON_XMLNode& node) const;

private:
  class CImpl;
  CImpl* _impl;
};

// Class ON_SunEx is the same as ON_Sun except that it overrides Azimuth() and Altitude() to calculate
// the sun's azimuth / altitude.
class ON_CLASS ON_SunEx : public ON_Sun
{
public:
  ON_SunEx();
  ON_SunEx(ON_XMLNode& model_node);
  ON_SunEx(const ON_SunEx& sun);
  virtual ~ON_SunEx();

  virtual const ON_Sun& operator = (const ON_Sun& sun) override;
  virtual const ON_SunEx& operator = (const ON_SunEx& sun);

  // Returns the azimuth of the sun in the sky (in degrees) as viewed by an observer on Earth. The value
  // increases Eastwards with North as zero. This value is not affected by the sun's 'north' setting.
  // If manual control is in effect, the stored value is returned. Otherwise the value is computed from the
  // values stored in the local date and time, latitude, longitude, time zone and daylight saving settings.
  // The stored value is not modified by this method (i.e., it is truly const).
  virtual double Azimuth(void) const override;

  // Returns the altitude of the sun in the sky (in degrees) as viewed by an observer on Earth.
  // If manual control is in effect, the stored value is returned. Otherwise the value is computed from the
  // values stored in the local date and time, latitude, longitude, time zone and daylight saving settings.
  // The stored value is not modified by this method (i.e., it is truly const).
  virtual double Altitude(void) const override;

private: // For internal use only.
  friend class ON_3dmRenderSettingsPrivate;
  virtual void InvalidateCache(void);

private:
  class CImpl;
  CImpl* _impl;
};

#endif
