/*
 *
 *  Copyright (C) 2000-2012, OFFIS e.V.
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
 *  Module: dcmsr
 *
 *  Author: Joerg Riesmeier
 *
 *  Purpose:
 *    classes: DSRImageReferenceValue
 *
 *  Last Update:      $Author: uli $
 *  Update Date:      $Date: 2012-01-06 09:13:08 $
 *  CVS/RCS Revision: $Revision: 1.21 $
 *  Status:           $State: Exp $
 *
 *  CVS/RCS Log at end of file
 *
 */


#ifndef DSRIMGVL_H
#define DSRIMGVL_H

#include "dcmtk/config/osconfig.h"   /* make sure OS specific configuration is included first */

#include "dcmtk/dcmsr/dsrtypes.h"
#include "dcmtk/dcmsr/dsrcomvl.h"
#include "dcmtk/dcmsr/dsrimgfr.h"


/*-----------------------*
 *  forward declaration  *
 *-----------------------*/

class DicomImage;


/*---------------------*
 *  class declaration  *
 *---------------------*/

/** Class for image reference values
 */
class DCMTK_DCMSR_EXPORT DSRImageReferenceValue
  : public DSRCompositeReferenceValue
{
    // allow access to getValuePtr()
    friend class DSRContentItem;

  public:

    /** default contructor
     */
    DSRImageReferenceValue();

    /** constructor.
     *  The UID pair is only set if it passed the validity check (see setValue()).
     ** @param  sopClassUID     referenced SOP class UID of the image object.
     *                          (VR=UI, mandatory)
     *  @param  sopInstanceUID  referenced SOP instance UID of the image object.
     *                          (VR=UI, mandatory)
     */
    DSRImageReferenceValue(const OFString &sopClassUID,
                           const OFString &sopInstanceUID);

    /** constructor.
     *  The UID 4-tuple is only set if it passed the validity check (see setValue()).
     ** @param  imageSOPClassUID      referenced SOP class UID of the image object.
     *                                (VR=UI, mandatory)
     *  @param  imageSOPInstanceUID   referenced SOP instance UID of the image object.
     *                                (VR=UI, mandatory)
     *  @param  pstateSOPClassUID     referenced SOP class UID of the presentation state
     *                                object. (VR=UI, optional)
     *  @param  pstateSOPInstanceUID  referenced SOP instance UID of the presentation state
     *                                object. (VR=UI, optional)
     */
    DSRImageReferenceValue(const OFString &imageSOPClassUID,
                           const OFString &imageSOPInstanceUID,
                           const OFString &pstateSOPClassUID,
                           const OFString &pstateSOPInstanceUID);

    /** copy constructor
     ** @param  referenceValue  image reference value to be copied (not checked !)
     */
    DSRImageReferenceValue(const DSRImageReferenceValue &referenceValue);

    /** copy constructor
     ** @param  imageReferenceValue   imagee reference value to be copied (not checked !)
     *  @param  pstateReferenceValue  presentation state reference value to be copied (not
     *                                checked !)
     */
    DSRImageReferenceValue(const DSRCompositeReferenceValue &imageReferenceValue,
                           const DSRCompositeReferenceValue &pstateReferenceValue);

    /** destructor
     */
    virtual ~DSRImageReferenceValue();

    /** assignment operator
     ** @param  referenceValue  image reference value to be copied (not checked !)
     ** @return reference to this image reference value after 'referenceValue' has been copied
     */
    DSRImageReferenceValue &operator=(const DSRImageReferenceValue &referenceValue);

    /** clear all internal variables.
     *  Since an empty image reference is invalid the reference becomes invalid afterwards.
     */
    virtual void clear();

    /** check whether the current image reference value is valid.
     *  The reference value is valid if SOP class UID and SOP instance UID are valid (see
     *  checkSOP...UID() for details) and the optional presentation state is valid (see
     *  checkPresentationState()).
     ** @return OFTrue if reference value is valid, OFFalse otherwise
     */
    virtual OFBool isValid() const;

    /** check whether the content is short.
     *  This method is used to check whether the rendered output of this content item can be
     *  expanded inline or not (used for renderHTML()).
     ** @param  flags  flag used to customize the output (see DSRTypes::HF_xxx)
     ** @return OFTrue if the content is short, OFFalse otherwise
     */
    virtual OFBool isShort(const size_t flags) const;

    /** print image reference.
     *  The output of a typical image reference value looks like this: (CT image,"1.2.3") or
     *  (CT image,"1.2.3"),(GSPS,"1.2.3.4") if a presentation state is present.
     *  If the SOP class UID is unknown the UID is printed instead of the related name.
     ** @param  stream  output stream to which the image reference value should be printed
     *  @param  flags   flag used to customize the output (see DSRTypes::PF_xxx)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition print(STD_NAMESPACE ostream &stream,
                              const size_t flags) const;

    /** read image reference from XML document
     ** @param  doc     document containing the XML file content
     *  @param  cursor  cursor pointing to the starting node
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition readXML(const DSRXMLDocument &doc,
                                DSRXMLCursor cursor);

    /** write image reference in XML format
     ** @param  stream  output stream to which the XML document is written
     *  @param  flags   flag used to customize the output (see DSRTypes::XF_xxx)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition writeXML(STD_NAMESPACE ostream &stream,
                                 const size_t flags) const;

    /** render image reference value in HTML/XHTML format
     ** @param  docStream    output stream to which the main HTML/XHTML document is written
     *  @param  annexStream  output stream to which the HTML/XHTML document annex is written
     *  @param  annexNumber  reference to the variable where the current annex number is
     *                       stored.  Value is increased automatically by 1 after a new entry
     *                       has been added.
     *  @param  flags        flag used to customize the output (see DSRTypes::HF_xxx)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition renderHTML(STD_NAMESPACE ostream &docStream,
                                   STD_NAMESPACE ostream &annexStream,
                                   size_t &annexNumber,
                                   const size_t flags) const;

    /** create an icon image from the given DICOM image and associate it with this image
     *  reference.  According to the DICOM standard, this icon image should be representative
     *  of the referenced image and the size of the icon image "may be no greater than 128 rows
     *  by 128 columns".  For monochrome images, either the first stored or an automatically
     *  computed min-max VOI window is selected.
     *  Please note that this icon image is only used in readItem() and writeItem() but not in
     *  the other input/output methods.
     ** @param  filename  name of the DICOM image file to be used to create the icon image
     *  @param  frame     number of the frame to be used to create the icon image
     *                    (0 = 1st frame)
     *  @param  width     width of the icon image (in pixels).  If 0 this value will be
     *                    calculated automatically based on the given 'height'.
     *  @param  height    height of the icon image (in pixels).  If 0 this value will be
     *                    calculated automatically based on the given 'width'.
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition createIconImage(const OFString &filename,
                                const unsigned long frame = 0,
                                const unsigned long width = 64,
                                const unsigned long height = 64);

    /** create an icon image from the given DICOM image and associate it with this image
     *  reference.  According to the DICOM standard, this icon image should be representative
     *  of the referenced image and the size of the icon image "may be no greater than 128 rows
     *  by 128 columns".  For monochrome images, either the first stored or an automatically
     *  computed min-max VOI window is selected.
     *  Please note that this icon image is only used in readItem() and writeItem() but not in
     *  the other input/output methods.
     ** @param  object  pointer to DICOM data structures (fileformat, dataset or item) that
     *                  contain the DICOM image to be used to create the icon image
     *  @param  xfer    transfer syntax of the 'object'.  In case of a fileformat or dataset,
     *                  the value EXS_Unknown is also allowed.
     *  @param  frame   number of the frame to be used to create the icon image (0 = 1st frame)
     *  @param  width   width of the icon image (in pixels).  If 0 this value will be
     *                  calculated automatically based on the given 'height'.
     *  @param  height  height of the icon image (in pixels).  If 0 this value will be
     *                  calculated automatically based on the given 'width'.
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition createIconImage(DcmObject *object,
                                const E_TransferSyntax xfer = EXS_Unknown,
                                const unsigned long frame = 0,
                                const unsigned long width = 64,
                                const unsigned long height = 64);

    /** create an icon image from the given DICOM image and associate it with this image
     *  reference.  According to the DICOM standard, this icon image should be representative
     *  of the referenced image and the size of the icon image "may be no greater than 128 rows
     *  by 128 columns".
     *  Please note that this icon image is only used in readItem() and writeItem() but not in
     *  the other input/output methods.
     ** @param  image   pointer to DICOM image to be used to create the icon image.  Only
     *                  single frame images should be passed since only the first frame is
     *                  used.
     *  @param  width   width of the icon image (in pixels).  If 0 this value will be
     *                  calculated automatically based on the given 'height'.
     *  @param  height  height of the icon image (in pixels).  If 0 this value will be
     *                  calculated automatically based on the given 'width'.
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition createIconImage(const DicomImage *image,
                                const unsigned long width = 64,
                                const unsigned long height = 64);

    /** delete the currently stored icon image, i.e.\ free the associated memory and "forget"
     *  the internal reference to it
     */
    void deleteIconImage();

    /** get reference to icon image associated with this image reference value (if any).
     *  Please note that the icon image might be invalid even if the pointer is not NULL.
     *  Therefore, the DicomImage::getStatus() method should always be called to check the
     *  status of the image.
     ** @return reference to icon image or NULL if none is present
     */
    const DicomImage *getIconImage() const
    {
        return IconImage;
    }

    /** get reference to image reference value
     ** @return reference to image reference value
     */
    inline const DSRImageReferenceValue &getValue() const
    {
        return *this;
    }

    /** get copy of image reference value
     ** @param  referenceValue  reference to variable in which the value should be stored
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition getValue(DSRImageReferenceValue &referenceValue) const;

    /** set image reference value.
     *  Before setting the reference it is checked (see checkXXX()).  If the value is
     *  invalid the current value is not replaced and remains unchanged.
     ** @param  referenceValue  value to be set
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition setValue(const DSRImageReferenceValue &referenceValue);

    /** get reference to presentation state value
     ** @return reference to presentation state value (might be empty or invalid)
     */
    inline const DSRCompositeReferenceValue &getPresentationState() const
    {
        return PresentationState;
    }

    /** set presentation state value.
     *  Before setting the reference it is checked (see checkPresentationState()).
     *  If the value is invalid the current value is not replaced and remains unchanged.
     ** @param  referenceValue  value to be set
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition setPresentationState(const DSRCompositeReferenceValue &referenceValue);

    /** get reference to list of referenced frame numbers
     ** @return reference to frame list
     */
    inline DSRImageFrameList &getFrameList()
    {
        return FrameList;
    }

    /** check whether the image reference applies to a specific frame.
     *  The image reference applies to a frame (of multiframe images) if the list of
     *  referenced frame numbers is empty or the frame number is part of the list.
     ** @param  frameNumber  number of the frame to be checked
     ** @return OFTrue if reference applies to the specified frame, OFFalse otherwise
     */
    OFBool appliesToFrame(const Sint32 frameNumber) const;


  protected:

    /** get pointer to image reference value
     ** @return pointer to image reference value (never NULL)
     */
    inline DSRImageReferenceValue *getValuePtr()
    {
        return this;
    }

    /** read image reference value from dataset
     ** @param  dataset  DICOM dataset from which the value should be read
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition readItem(DcmItem &dataset);

    /** write image reference value to dataset
     ** @param  dataset  DICOM dataset to which the value should be written
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition writeItem(DcmItem &dataset) const;

    /** check the specified SOP class UID for validity.
     *  The only check that is currently performed is that the UID is not empty.  Later on
     *  it might be checked whether the specified SOP class is really an image storage SOP
     *  class.
     ** @param  sopClassUID  SOP class UID to be checked
     ** @return OFTrue if SOP class UID is valid, OFFalse otherwise
     */
    virtual OFBool checkSOPClassUID(const OFString &sopClassUID) const;

    /** check the presentation state object for validity.
     *  The presentation state object is "valid" if both UIDs are empty or both are not
     *  empty and SOP class UID refers to a softcopy presentation state (see
     *  DSRTypes::E_PresentationStateType for a list of supported SOP classes).
     ** @param  referenceValue  value to be checked
     ** @return OFTrue if presentation state object is valid, OFFalse otherwise
     */
    OFBool checkPresentationState(const DSRCompositeReferenceValue &referenceValue) const;


  private:

    /// composite reference value (SOP class/instance UID) to presentation state (optional)
    DSRCompositeReferenceValue PresentationState;
    /// list of referenced frame numbers (associated DICOM VR=IS, VM=1-n, type 1C)
    DSRImageFrameList FrameList;
    /// icon image from Icon Image Sequence (optional)
    DicomImage *IconImage;
};


#endif


/*
 *  CVS/RCS Log:
 *  $Log: dsrimgvl.h,v $
 *  Revision 1.21  2012-01-06 09:13:08  uli
 *  Make it possible to build dcmsr as a DLL.
 *
 *  Revision 1.20  2012-01-03 10:58:04  joergr
 *  Added support for icon image to IMAGE content item (introduced with CP-217).
 *
 *  Revision 1.19  2011-08-02 08:32:34  joergr
 *  Added more general support for softcopy presentation states (not only GSPS).
 *
 *  Revision 1.18  2011-08-02 06:26:31  joergr
 *  Fixed typos and/or minor formatting issues.
 *
 *  Revision 1.17  2010-10-14 13:16:32  joergr
 *  Updated copyright header. Added reference to COPYRIGHT file.
 *
 *  Revision 1.16  2009-10-13 14:57:50  uli
 *  Switched to logging mechanism provided by the "new" oflog module.
 *
 *  Revision 1.15  2007-11-15 16:33:30  joergr
 *  Added support for output in XHTML 1.1 format.
 *
 *  Revision 1.14  2006/08/15 16:40:03  meichel
 *  Updated the code in module dcmsr to correctly compile when
 *    all standard C++ classes remain in namespace std.
 *
 *  Revision 1.13  2005/12/08 16:05:06  meichel
 *  Changed include path schema for all DCMTK header files
 *
 *  Revision 1.12  2003/10/06 09:52:35  joergr
 *  Added comment that the optional IconImageSequence is not yet supported.
 *
 *  Revision 1.11  2003/08/07 18:01:42  joergr
 *  Removed libxml dependency from header files.
 *
 *  Revision 1.10  2003/08/07 12:42:38  joergr
 *  Added readXML functionality.
 *
 *  Revision 1.9  2001/09/26 13:04:09  meichel
 *  Adapted dcmsr to class OFCondition
 *
 *  Revision 1.8  2001/06/01 15:51:01  meichel
 *  Updated copyright header
 *
 *  Revision 1.7  2000/11/06 11:17:21  joergr
 *  Moved some protected methods to public part.
 *
 *  Revision 1.6  2000/11/01 16:23:21  joergr
 *  Added support for conversion to XML.
 *
 *  Revision 1.5  2000/10/26 14:18:27  joergr
 *  Updated comments.
 *
 *  Revision 1.4  2000/10/20 10:15:42  joergr
 *  Renamed class DSRReferenceValue to DSRCompositeReferenceValue.
 *
 *  Revision 1.3  2000/10/18 17:04:23  joergr
 *  Added methods allowing direct access to certain content item values.
 *  Added doc++ comments.
 *
 *  Revision 1.2  2000/10/16 11:54:12  joergr
 *  Added new method checking whether an image content item applies to a
 *  certain frame.
 *
 *  Revision 1.1  2000/10/13 07:49:28  joergr
 *  Added new module 'dcmsr' providing access to DICOM structured reporting
 *  documents (supplement 23).  Doc++ documentation not yet completed.
 *
 *
 */
