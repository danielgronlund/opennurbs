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

#if !defined(ON_SKYLIGHT_INC_)
#define ON_SKYLIGHT_INC_

class ON_CLASS ON_Skylight
{
public:
  ON_Skylight();
  ON_Skylight(ON_XMLNode& model_node);
  ON_Skylight(const ON_Skylight& sl);
  virtual ~ON_Skylight();

  virtual const ON_Skylight& operator = (const ON_Skylight& sl);

  virtual bool operator == (const ON_Skylight& sl) const;
  virtual bool operator != (const ON_Skylight& sl) const;

  // Returns true if the skylight is enabled, else false.
  virtual bool On(void) const;

  // Set the skylight enabled state.
  virtual void SetOn(bool b);

  // Returns the skylight shadow intensity. This is unused at present.
  virtual double ShadowIntensity(void) const;

  // Set the skylight shadow intensity. This is unused at present.
  virtual void SetShadowIntensity(double d);

  // Emergency virtual function for future expansion.
  virtual void* EVF(const wchar_t* func, void* data);

public: // These methods are only here to support deprecated C# SDK methods.
        // Please use the equivalent methods in ON_3dmRenderSettings.
  /* DEPRECATED*/ bool EnvironmentOverride(void) const;
  /* DEPRECATED*/ void SetEnvironmentOverride(bool on);
  /* DEPRECATED*/ ON_UUID EnvironmentId(void) const;
  /* DEPRECATED*/ void SetEnvironmentId(const ON_UUID& id);

private: // For internal use only.
  friend class ON_3dmRenderSettingsPrivate;
  virtual void InvalidateCache(void);

private:
  class CImpl;
  CImpl* m_impl;
};

#endif
