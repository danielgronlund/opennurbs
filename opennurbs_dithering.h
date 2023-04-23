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

#if !defined(ON_DITHERING_INC_)
#define ON_DITHERING_INC_

class ON_CLASS ON_Dithering
{
public:
  ON_Dithering();
  ON_Dithering(ON_XMLNode& model_node);
  ON_Dithering(const ON_Dithering& dit);
  virtual ~ON_Dithering();

  virtual const ON_Dithering& operator = (const ON_Dithering& dit);

  virtual bool operator == (const ON_Dithering& dit) const;
  virtual bool operator != (const ON_Dithering& dit) const;

  // Get dithering on / off state.
  virtual bool On(void) const;

  // Set dithering on or off.
  virtual void SetOn(bool b);

  enum class Methods { SimpleNoise, FloydSteinberg };

  // Get the dithering method.
  virtual Methods Method(void) const;

  // Set the dithering method.
  virtual void SetMethod(Methods m);

  // Returns the CRC of the dithering state.
  virtual ON__UINT32 DataCRC(ON__UINT32 current_remainder) const;

  // Emergency virtual function for future expansion.
  virtual void* EVF(const wchar_t* func, void* data);

private: // For internal use only.
  friend class ON_3dmRenderSettingsPrivate;
  virtual void InvalidateCache(void);

private:
  class CImpl;
  CImpl* m_impl;
};

#endif
