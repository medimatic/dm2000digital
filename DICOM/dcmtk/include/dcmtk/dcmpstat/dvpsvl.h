/*
 *
 *  Copyright (C) 1998-2012, OFFIS e.V.
 *  All rights reserved.  See COPYRIGHT file for details.
 *
 *  This software and supporting documentation were developed by
 *
 *    OFFIS e.V.
 *    R&D Division Health
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *
 *  Module: dcmpstat
 *
 *  Author: Marco Eichelberg
 *
 *  Purpose:
 *    classes: DVPSVOILUT
 *
 *  Last Update:      $Author: uli $
 *  Update Date:      $Date: 2012-01-06 10:05:51 $
 *  CVS/RCS Revision: $Revision: 1.11 $
 *  Status:           $State: Exp $
 *
 *  CVS/RCS Log at end of file
 *
 */

#ifndef DVPSVL_H
#define DVPSVL_H

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */
#include "dcmtk/dcmpstat/dvpstyp.h"
#include "dcmtk/dcmpstat/dpdefine.h"
#include "dcmtk/ofstd/ofstring.h"
#include "dcmtk/dcmdata/dctk.h"

class DVPSSoftcopyVOI;

/** the representation of one VOI LUT in a DICOM image.
 */

class DCMTK_DCMPSTAT_EXPORT DVPSVOILUT
{
public:
  /// default constructor
  DVPSVOILUT();

  /// copy constructor
  DVPSVOILUT(const DVPSVOILUT& copy);

  /** clone method.
   *  @return a pointer to a new DVPSVOILUT object containing
   *  a copy of this object.
   */
  DVPSVOILUT *clone() { return new DVPSVOILUT(*this); }

  /// destructor
  virtual ~DVPSVOILUT();

  /** reads a VOI LUT from a DICOM dataset.
   *  The DICOM elements of the VOI LUT item are copied
   *  from the dataset to this object.
   *  The completeness of the item (presence of all required elements,
   *  value multiplicity) is checked.
   *  If this method returns an error code, the object is in undefined state afterwards.
   *  @param dset the item of the VOI LUT Sequence from which the data is to be read
   *  @return EC_Normal if successful, an error code otherwise.
   */
  OFCondition read(DcmItem &dset);

  /** resets the object to initial state.
   *  After this call, the object is in the same state as after
   *  creation with the default constructor.
   */
  void clear();

  /** gets the LUT explanation for this VOI LUT.
   *  If no explanation exists, NULL is returned.
   *  @return LUT explanation or NULL
   */
  const char *getExplanation();

  /** assigns the contents of this VOI LUT to the
   *  references passed as parameters.
   *  @param reference to the Softcopy VOI in which the LUT is stored.
   */
  OFCondition assign(DVPSSoftcopyVOI& voi);

private:

  /// private undefined assignment operator
  DVPSVOILUT& operator=(const DVPSVOILUT&);

  /// Module=VOI_LUT, VR=xs, VM=3, Type 1c
  DcmUnsignedShort         voiLUTDescriptor;
  /// Module=VOI_LUT, VR=LO, VM=1, Type 3
  DcmLongString            voiLUTExplanation;
  /// Module=VOI_LUT, VR=xs, VM=1-n, Type 1c
  DcmUnsignedShort         voiLUTData;
};

#endif

/*
 *  $Log: dvpsvl.h,v $
 *  Revision 1.11  2012-01-06 10:05:51  uli
 *  Make it possible to build dcmpstat as a DLL.
 *
 *  Revision 1.10  2010-10-14 13:16:37  joergr
 *  Updated copyright header. Added reference to COPYRIGHT file.
 *
 *  Revision 1.9  2010-10-07 14:31:36  joergr
 *  Removed leading underscore characters from preprocessor symbols (reserved).
 *
 *  Revision 1.8  2009-11-24 14:12:58  uli
 *  Switched to logging mechanism provided by the "new" oflog module.
 *
 *  Revision 1.7  2005-12-08 16:04:11  meichel
 *  Changed include path schema for all DCMTK header files
 *
 *  Revision 1.6  2001/09/26 15:36:18  meichel
 *  Adapted dcmpstat to class OFCondition
 *
 *  Revision 1.5  2001/06/01 15:50:25  meichel
 *  Updated copyright header
 *
 *  Revision 1.4  2000/06/02 16:00:54  meichel
 *  Adapted all dcmpstat classes to use OFConsole for log and error output
 *
 *  Revision 1.3  2000/03/08 16:28:59  meichel
 *  Updated copyright header.
 *
 *  Revision 1.2  1999/07/22 16:39:15  meichel
 *  Adapted dcmpstat data structures and API to supplement 33 letter ballot text.
 *
 *  Revision 1.1  1998/12/22 17:57:09  meichel
 *  Implemented Presentation State interface for overlays,
 *    VOI LUTs, VOI windows, curves. Added test program that
 *    allows to add curve data to DICOM images.
 *
 *
 */
