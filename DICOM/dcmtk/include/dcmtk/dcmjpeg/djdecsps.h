/*
 *
 *  Copyright (C) 1997-2011, OFFIS e.V.
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
 *  Module:  dcmjpeg
 *
 *  Author:  Marco Eichelberg
 *
 *  Purpose: Codec class for decoding JPEG Spectral Selection (lossy, 8/12-bit)
 *
 *  Last Update:      $Author: uli $
 *  Update Date:      $Date: 2011-12-14 10:33:20 $
 *  CVS/RCS Revision: $Revision: 1.4 $
 *  Status:           $State: Exp $
 *
 *  CVS/RCS Log at end of file
 *
 */

#ifndef DJDECSPS_H
#define DJDECSPS_H

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmjpeg/djcodecd.h" /* for class DJCodecDecoder */


/** Decoder class for JPEG Spectral Selection (lossy, 8/12-bit)
 */
class DCMTK_DCMJPEG_EXPORT DJDecoderSpectralSelection : public DJCodecDecoder
{
public: 

  /// default constructor
  DJDecoderSpectralSelection();

  /// destructor
  virtual ~DJDecoderSpectralSelection();

  /** returns the transfer syntax that this particular codec
   *  is able to encode and decode.
   *  @return supported transfer syntax
   */
  virtual E_TransferSyntax supportedTransferSyntax() const;

private:

  /** creates an instance of the compression library to be used for decoding.
   *  @param toRepParam representation parameter passed to decode()
   *  @param cp codec parameter passed to decode()
   *  @param bitsPerSample bits per sample for the image data
   *  @param isYBR flag indicating whether DICOM photometric interpretation is YCbCr
   *  @return pointer to newly allocated decoder object
   */
  virtual DJDecoder *createDecoderInstance(
    const DcmRepresentationParameter * toRepParam,
    const DJCodecParameter *cp,
    Uint8 bitsPerSample,
    OFBool isYBR) const;

};

#endif

/*
 * CVS/RCS Log
 * $Log: djdecsps.h,v $
 * Revision 1.4  2011-12-14 10:33:20  uli
 * Make it possible to decently build dcmjpeg as a DLL.
 *
 * Revision 1.3  2010-10-14 13:17:17  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.2  2005-12-08 16:59:20  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.1  2001/11/13 15:56:21  meichel
 * Initial release of module dcmjpeg
 *
 *
 */
