// Created on: 1992-04-06
// Created by: Christophe MARION
// Copyright (c) 1992-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _HLRAlgo_EdgesBlock_HeaderFile
#define _HLRAlgo_EdgesBlock_HeaderFile

#include <Standard.hxx>
#include <Standard_Type.hxx>

#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_Array1OfBoolean.hxx>
#include <Standard_Integer.hxx>
#include <MMgt_TShared.hxx>
#include <TopAbs_Orientation.hxx>
#include <Standard_Boolean.hxx>
#include <Standard_Address.hxx>


class HLRAlgo_EdgesBlock;
DEFINE_STANDARD_HANDLE(HLRAlgo_EdgesBlock, MMgt_TShared)

//! An EdgesBlock is a set of Edges. It is used by the
//! DataStructure to structure the Edges.
//!
//! An EdgesBlock contains :
//!
//! * An Array  of index of Edges.
//!
//! * An Array of flagsf ( Orientation
//! OutLine
//! Internal
//! Double
//! IsoLine)
class HLRAlgo_EdgesBlock : public MMgt_TShared
{

public:

  //! Create a Block of Edges for a wire.
  Standard_EXPORT HLRAlgo_EdgesBlock(const Standard_Integer NbEdges);

  Standard_Integer NbEdges() const { return myEdges.Upper(); }

  void Edge (const Standard_Integer I, const Standard_Integer EI) { myEdges(I) = EI; }

  Standard_Integer Edge (const Standard_Integer I) const { return myEdges(I); }

  void Orientation (const Standard_Integer I, const TopAbs_Orientation Or)
  {
    myFlags(I) &= ~EMaskOrient;
    myFlags(I) |= (Or & EMaskOrient);
  }

  TopAbs_Orientation Orientation (const Standard_Integer I) const
  {
    return ((TopAbs_Orientation)(myFlags(I) & EMaskOrient));
  }

  Standard_Boolean OutLine (const Standard_Integer I) const { return (myFlags(I) & EMaskOutLine) != 0; }

  void OutLine (const Standard_Integer I, const Standard_Boolean B)
  {
    if (B) myFlags(I) |=  EMaskOutLine;
    else   myFlags(I) &= ~EMaskOutLine;
  }

  Standard_Boolean Internal (const Standard_Integer I) const { return (myFlags(I) & EMaskInternal) != 0; }

  void Internal (const Standard_Integer I, const Standard_Boolean B)
  {
    if (B) myFlags(I) |=  EMaskInternal;
    else   myFlags(I) &= ~EMaskInternal;
  }

  Standard_Boolean Double (const Standard_Integer I) const { return (myFlags(I) & EMaskDouble) != 0; }

  void Double (const Standard_Integer I, const Standard_Boolean B)
  {
    if (B) myFlags(I) |=  EMaskDouble;
    else   myFlags(I) &= ~EMaskDouble;
  }

  Standard_Boolean IsoLine (const Standard_Integer I) const { return (myFlags(I) & EMaskIsoLine) != 0; }

  void IsoLine (const Standard_Integer I, const Standard_Boolean B)
  {
    if (B) myFlags(I) |=  EMaskIsoLine;
    else   myFlags(I) &= ~EMaskIsoLine;
  }

  Standard_EXPORT void UpdateMinMax (const Standard_Address TotMinMax);

  Standard_Address MinMax() const { return (Standard_Address )&myMinMax; }

  DEFINE_STANDARD_RTTIEXT(HLRAlgo_EdgesBlock,MMgt_TShared)

protected:

  enum EMskFlags
  {
    EMaskOrient   = 15,
    EMaskOutLine  = 16,
    EMaskInternal = 32,
    EMaskDouble   = 64,
    EMaskIsoLine  = 128
  };

private:

  TColStd_Array1OfInteger myEdges;
  TColStd_Array1OfInteger myFlags;
  Standard_Integer myMinMax[16];

};

#endif // _HLRAlgo_EdgesBlock_HeaderFile
