/*
 *
 *  Copyright (C) 1994-2011, OFFIS e.V.
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
 *  Module:  dcmdata
 *
 *  Author:  Andreas Barth
 *
 *  Purpose: Interface of class DcmCharString
 *
 *  Last Update:      $Author: uli $
 *  Update Date:      $Date: 2011-12-14 09:04:11 $
 *  CVS/RCS Revision: $Revision: 1.22 $
 *  Status:           $State: Exp $
 *
 *  CVS/RCS Log at end of file
 *
 */


#ifndef DCCHRSTR_H
#define DCCHRSTR_H

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

//
// This implementation does not support 16 bit character sets. Since 8 bit
// character sets are supported by the class DcmByteString the class
// DcmCharString is derived from DcmByteString without any extensions.
//
// If the extension for 16 bit character sets will be implemented this class
// must be derived directly from DcmElement. This class is designed to support
// the value representations (LO, LT, PN, SH, ST, UT). They are a problem because
// their value width (1, 2, .. Bytes) is specified by the element
// SpecificCharacterSet (0008, 0005) and an implementation must support
// different value widths that cannot be derived from the value representation.
//

#include "dcmtk/dcmdata/dcbytstr.h"


/** base class for DICOM elements with value representation LO, LT, PN, SH, ST, UT
 */
class DCMTK_DCMDATA_EXPORT DcmCharString
  : public DcmByteString
{

  public:

    /** constructor.
     *  Create new element from given tag and length.
     *  @param tag DICOM tag for the new element
     *  @param len value length for the new element
     */
    DcmCharString(const DcmTag &tag,
                  const Uint32 len);

    /** copy constructor
     *  @param old element to be copied
     */
    DcmCharString(const DcmCharString &old);

    /** destructor
     */
    virtual ~DcmCharString();

    /** assignment operator
     *  @param obj element to be assigned/copied
     *  @return reference to this object
     */
    DcmCharString &operator=(const DcmCharString &obj);

    /** clone method
     *  @return deep copy of this object
     */
    virtual DcmObject *clone() const
    {
      return new DcmCharString(*this);
    }

    /** Virtual object copying. This method can be used for DcmObject
     *  and derived classes to get a deep copy of an object. Internally
     *  the assignment operator is called if the given DcmObject parameter
     *  is of the same type as "this" object instance. If not, an error
     *  is returned. This function permits copying an object by value
     *  in a virtual way which therefore is different to just calling the
     *  assignment operator of DcmElement which could result in slicing
     *  the object.
     *  @param rhs - [in] The instance to copy from. Has to be of the same
     *                class type as "this" object
     *  @return EC_Normal if copying was successful, error otherwise
     */
    virtual OFCondition copyFrom(const DcmObject& rhs);

    /** check the currently stored string value.
     *  Checks every string component for the maximum length specified for the particular
     *  value representation.
     *  @param autocorrect correct value and value component length if OFTrue.
     *    NB: This parameter does currently nothing since it is unknown to this class
     *        whether a character consists of one or more bytes.  To be fixed in a future
     *        version when multi-byte character sets are (hopefully) supported.
     *  @return status, EC_Normal if value length is correct, an error code otherwise
     */
    virtual OFCondition verify(const OFBool autocorrect = OFFalse);

    /** check if this element contains non-ASCII characters. Please note that this check
     *  is pretty simple and only works for single-byte character sets that do include
     *  the 7-bit ASCII codes, e.g. for the ISO 8859 family. In other words: All character
     *  codes below 128 are considered to be ASCII codes and all others are considered to
     *  be non-ASCII.
     *  @param checkAllStrings not used in this class
     *  @return true if element contains non-ASCII characters, false otherwise
     */
    virtual OFBool containsExtendedCharacters(const OFBool checkAllStrings = OFFalse);

    /** check if this element is affected by SpecificCharacterSet
     *  @return always returns true since all derived VR classes are affected by the
     *    SpecificCharacterSet (0008,0005) element
     */
    virtual OFBool isAffectedBySpecificCharacterSet() const;

    /** convert this element value from the currently selected source character set to
     *  the currently selected destination character set
     *  @param converter character set converter to be used to convert the element value
     *  @return always returns EC_Normal, since nothing to do in this base class
     */
    virtual OFCondition convertCharacterSet(DcmSpecificCharacterSet &converter);

  protected:

    /** delimiter characters specifying when to switch back to the default character set
     *  (in case code extension techniques like ISO 2022 are used)
     *  @param characters delimiter characters to be used for character set conversion
     */
    void setDelimiterChars(const OFString &characters) { delimiterChars = characters; }

  private:

    /// delimiter characters specifying when to switch back to the default character set
    /// (in case code extension techniques like ISO 2022 are used)
    OFString delimiterChars;
};


#endif // DCCHRSTR_H


/*
 * CVS/RCS Log:
 * $Log: dcchrstr.h,v $
 * Revision 1.22  2011-12-14 09:04:11  uli
 * Make it possible to accurately build dcmdata and libi2d as DLLs.
 *
 * Revision 1.21  2011-11-14 11:11:42  joergr
 * Slightly improved API documentation on containsExtendedCharacters() and
 * isAffectedBySpecificCharacterSet().
 *
 * Revision 1.20  2011-11-08 15:51:37  joergr
 * Added support for converting files, datasets and element values to any DICOM
 * character set that does not require code extension techniques (if compiled
 * with and supported by libiconv), not only to UTF-8 as before.
 *
 * Revision 1.19  2011-11-01 14:53:59  joergr
 * Added support for code extensions (escape sequences) according to ISO 2022
 * to the character set conversion code.
 *
 * Revision 1.18  2011-10-26 16:20:18  joergr
 * Added method that allows for converting a dataset or element value to UTF-8.
 *
 * Revision 1.17  2011-10-18 14:00:09  joergr
 * Added support for embedded NULL bytes in string element values.
 *
 * Revision 1.16  2010-10-14 13:15:40  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.15  2008-07-17 11:19:48  onken
 * Updated copyFrom() documentation.
 *
 * Revision 1.14  2008-07-17 10:30:22  onken
 * Implemented copyFrom() method for complete DcmObject class hierarchy, which
 * permits setting an instance's value from an existing object. Implemented
 * assignment operator where necessary.
 *
 * Revision 1.13  2006-12-15 14:18:07  joergr
 * Added new method that checks whether a DICOM object or element is affected
 * by SpecificCharacterSet (0008,0005).
 *
 * Revision 1.12  2006/12/13 13:58:15  joergr
 * Added new optional parameter "checkAllStrings" to method containsExtended
 * Characters().
 *
 * Revision 1.11  2006/05/11 08:52:09  joergr
 * Moved checkForNonASCIICharacters() from application to library.
 *
 * Revision 1.10  2005/12/08 16:28:00  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.9  2004/07/01 12:28:25  meichel
 * Introduced virtual clone method for DcmObject and derived classes.
 *
 * Revision 1.8  2002/12/06 12:49:08  joergr
 * Enhanced "print()" function by re-working the implementation and replacing
 * the boolean "showFullData" parameter by a more general integer flag.
 * Added doc++ documentation.
 * Made source code formatting more consistent with other modules/files.
 *
 * Revision 1.7  2001/06/01 15:48:33  meichel
 * Updated copyright header
 *
 * Revision 1.6  2000/03/08 16:26:11  meichel
 * Updated copyright header.
 *
 * Revision 1.5  1999/03/31 09:24:30  meichel
 * Updated copyright header in module dcmdata
 *
 *
 */
