/*
 *
 *  Copyright (C) 2002-2012, OFFIS e.V.
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
 *    classes: DSRSOPInstanceReferenceList
 *             - InstanceStruct, SeriesStruct, StudyStruct
 *
 *  Last Update:      $Author: uli $
 *  Update Date:      $Date: 2012-01-06 09:13:11 $
 *  CVS/RCS Revision: $Revision: 1.18 $
 *  Status:           $State: Exp $
 *
 *  CVS/RCS Log at end of file
 *
 */


#ifndef DSRSOPRF_H
#define DSRSOPRF_H

#include "dcmtk/config/osconfig.h"   /* make sure OS specific configuration is included first */

#include "dcmtk/ofstd/oflist.h"
#include "dcmtk/ofstd/ofstring.h"
#include "dcmtk/ofstd/ofcond.h"

#include "dcmtk/dcmdata/dcitem.h"
#include "dcmtk/dcmdata/dctagkey.h"

#include "dcmtk/dcmsr/dsrtypes.h"
#include "dcmtk/dcmsr/dsrcodvl.h"


/*---------------------*
 *  class declaration  *
 *---------------------*/

/** Class for SOP instance reference lists
 */
class DCMTK_DCMSR_EXPORT DSRSOPInstanceReferenceList
  : public DSRTypes
{

  public:

    /** Internal structure defining the instance list items
     */
    struct DCMTK_DCMSR_EXPORT InstanceStruct
    {
        /** constructor
         ** @param  sopClassUID  SOP class UID
         ** @param  instanceUID  SOP instance UID
         */
        InstanceStruct(const OFString &sopClassUID,
                       const OFString &instanceUID);

        /** clear additional information
         */
        void clear();

        /// SOP Class UID (VR=UI, VM=1, Type=1)
        const OFString SOPClassUID;
        /// SOP Instance UID (VR=UI, VM=1, Type=1)
        const OFString InstanceUID;
        /// Purpose of Reference Code Sequence (VR=SQ, VM=1, Type=3)
        DSRCodedEntryValue PurposeOfReference;
    };

    /** Internal structure defining the series list items
     */
    struct DCMTK_DCMSR_EXPORT SeriesStruct
    {
        /** constructor
         ** @param  seriesUID  series instance UID
         */
        SeriesStruct(const OFString &seriesUID);

        /** destructor
         */
        ~SeriesStruct();

        /** get number of instance stored in the list of instances
         ** @return number of instances
         */
        size_t getNumberOfInstances() const;

        /** read instance level attributes from dataset
         ** @param  dataset  DICOM dataset from which the list should be read
         ** @return status, EC_Normal if successful, an error code otherwise
         */
        OFCondition read(DcmItem &dataset);

        /** write series and instance level attributes to dataset
         ** @param  dataset  DICOM dataset to which the list should be written
         ** @return status, EC_Normal if successful, an error code otherwise
         */
        OFCondition write(DcmItem &dataset) const;

        /** read series and instance level attributes from XML document
         ** @param  doc     document containing the XML file content
         *  @param  cursor  cursor pointing to the starting node
         ** @return status, EC_Normal if successful, an error code otherwise
         */
        OFCondition readXML(const DSRXMLDocument &doc,
                            DSRXMLCursor cursor);

        /** write series and instance level attributes in XML format
         ** @param  stream  output stream to which the XML document is written
         *  @param  flags   optional flag used to customize the output (see DSRTypes::XF_xxx)
         ** @return status, EC_Normal if successful, an error code otherwise
         */
        OFCondition writeXML(STD_NAMESPACE ostream &stream,
                             const size_t flags = 0) const;

        /** set cursor to the specified instance (if existent)
         ** @param  instanceUID  SOP instance UID of the entry to be searched for
         ** @return pointer to the instance structure if successful, NULL otherwise
         */
        InstanceStruct *gotoInstance(const OFString &instanceUID);

        /** select the first item in the list.
         *  That means the first instance in the current series.
         ** @return status, EC_Normal if successful, an error code otherwise
         */
        OFCondition gotoFirstItem();

        /** select the next item in the list.
         *  That means the next instance in the current series (if available).
         ** @return status, EC_Normal if successful, an error code otherwise
         */
        OFCondition gotoNextItem();

        /** add new entry to the list of instances (if not already existent).
         *  Finally, the specified item is selected as the current one.
         ** @param  sopClassUID  SOP class UID of the entry to be added
         *  @param  instanceUID  SOP instance UID of the entry to be added
         ** @return status, EC_Normal if successful, an error code otherwise
         */
        OFCondition addItem(const OFString &sopClassUID,
                            const OFString &instanceUID);

        /** remove the current item from the list of instances.
         *  After successful removal the cursor is set to the next valid position.
         ** @return status, EC_Normal if successful, an error code otherwise
         */
        OFCondition removeItem();

        /// Series Instance UID (VR=UI, VM=1, Type=1)
        const OFString SeriesUID;
        /// Retrieve Application Entity Title (VR=AE, VM=1-n, Type=3)
        OFString RetrieveAETitle;
        /// Storage Media File Set ID (VR=SH, VM=1, Type=3)
        OFString StorageMediaFileSetID;
        /// Storage Media File Set UID (VR=UI, VM=1, Type=3)
        OFString StorageMediaFileSetUID;

        /// list of referenced instances
        OFList<InstanceStruct *> InstanceList;
        /// currently selected instance (cursor)
        OFListIterator(InstanceStruct *) Iterator;
    };

    /** Internal structure defining the study list items
     */
    struct DCMTK_DCMSR_EXPORT StudyStruct
    {
        /** constructor
         ** @param  studyUID  study instance UID
         */
        StudyStruct(const OFString &studyUID);

        /** destructor
         */
        ~StudyStruct();

        /** get number of instance stored in the list of series
         ** @return number of instances
         */
        size_t getNumberOfInstances() const;

        /** read series and instance level from dataset
         ** @param  dataset  DICOM dataset from which the list should be read
         ** @return status, EC_Normal if successful, an error code otherwise
         */
        OFCondition read(DcmItem &dataset);

        /** write study, series and instance level attributes to dataset
         ** @param  dataset  DICOM dataset to which the list should be written
         ** @return status, EC_Normal if successful, an error code otherwise
         */
        OFCondition write(DcmItem &dataset) const;

        /** read study, series and instance level attributes from XML document
         ** @param  doc     document containing the XML file content
         *  @param  cursor  cursor pointing to the starting node
         ** @return status, EC_Normal if successful, an error code otherwise
         */
        OFCondition readXML(const DSRXMLDocument &doc,
                            DSRXMLCursor cursor);

        /** write study, series and instance level attributes in XML format
         ** @param  stream  output stream to which the XML document is written
         *  @param  flags   optional flag used to customize the output (see DSRTypes::XF_xxx)
         ** @return status, EC_Normal if successful, an error code otherwise
         */
        OFCondition writeXML(STD_NAMESPACE ostream &stream,
                             const size_t flags = 0) const;

        /** set cursor to the specified series entry (if existent)
         ** @param  seriesUID  series instance UID of the entry to be searched for
         ** @return pointer to the series structure if successful, NULL otherwise
         */
        SeriesStruct *gotoSeries(const OFString &seriesUID);

        /** set cursor to the specified instance entry (if existent)
         ** @param  instanceUID  SOP instance UID of the entry to be searched for
         ** @return pointer to the instance structure if successful, NULL otherwise
         */
        InstanceStruct *gotoInstance(const OFString &instanceUID);

        /** select the first item in the list.
         *  That means the first instance in the first series of the current study.
         ** @return status, EC_Normal if successful, an error code otherwise
         */
        OFCondition gotoFirstItem();

        /** select the next item in the list.
         *  That means the next instance in the current series, or the first instance
         *  in the next series (if available).
         ** @return status, EC_Normal if successful, an error code otherwise
         */
        OFCondition gotoNextItem();

        /** add new entry to the list of series and instances (if not already existent).
         *  Finally, the specified items are selected as the current one.
         ** @param  seriesUID    series instance UID of the entry to be added
         *  @param  sopClassUID  SOP class UID of the entry to be added
         *  @param  instanceUID  SOP instance UID of the entry to be added
         ** @return status, EC_Normal if successful, an error code otherwise
         */
        OFCondition addItem(const OFString &seriesUID,
                            const OFString &sopClassUID,
                            const OFString &instanceUID);

        /** remove the current item from the list of series and instances.
         *  After successful removal the cursors are set to the next valid position.
         ** @return status, EC_Normal if successful, an error code otherwise
         */
        OFCondition removeItem();

        /** remove empty/incomplete items from the list.
         *  (e.g. series with no instances)
         *  Please note that this function modifies the value of 'Iterator'.
         */
        void removeIncompleteItems();

        /// Study Instance UID (VR=UI, VM=1, Type=1)
        const OFString StudyUID;

        /// list of referenced series
        OFList<SeriesStruct *> SeriesList;
        /// currently selected series (cursor)
        OFListIterator(SeriesStruct *) Iterator;
    };


    /** constructor
     ** @param  sequence  DICOM tag specifying the attribute (sequence) of the reference list
     */
    DSRSOPInstanceReferenceList(const DcmTagKey &sequence);

    /** destructor
     */
    ~DSRSOPInstanceReferenceList();

    /** clear list of references
     */
    void clear();

    /** check whether list of references is empty
     ** @return OFTrue if list is empty, OFFalse otherwise
     */
    OFBool empty() const;

    /** get number of instance stored in the list of references
     ** @return number of instances
     */
    size_t getNumberOfInstances() const;

    /** read list of referenced SOP instances.
     *  The hierarchical structure is automatically reorganized in a way that each study,
     *  each series (within a study) and each instance (within a series) only exist once,
     *  i.e. the structure might look different when written back to a dataset.  However,
     *  the content is identical and this way of storing information saves storage space.
     ** @param  dataset  DICOM dataset from which the data should be read
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition read(DcmItem &dataset);

    /** write list of referenced SOP instances.
     *  Does nothing if list is empty.
     ** @param  dataset  DICOM dataset to which the data should be written
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition write(DcmItem &dataset) const;

    /** read list of references from XML document.
     *  The hierarchical structure is automatically reorganized in a way that each study,
     *  each series (within a study) and each instance (within a series) only exist once,
     *  i.e. the structure might look different when written back to a dataset.  However,
     *  the content is identical and this way of storing information saves storage space.
     ** @param  doc     document containing the XML file content
     *  @param  cursor  cursor pointing to the starting node
     *  @param  flags   optional flag used to customize the reading process (see DSRTypes::XF_xxx)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition readXML(const DSRXMLDocument &doc,
                        DSRXMLCursor cursor,
                        const size_t flags);

    /** write current list of references in XML format
     ** @param  stream  output stream to which the XML data is written
     *  @param  flags   optional flag used to customize the output (see DSRTypes::XF_xxx)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition writeXML(STD_NAMESPACE ostream &stream,
                         const size_t flags = 0) const;

    /** add the specified item to the list of references.
     *  Internally the item is inserted into the hierarchical structure of studies, series
     *  and instances, if not already contained in the list. In any case the specified item
     *  is selected as the current one.
     ** @param  studyUID     study instance UID of the entry to be added
     *  @param  seriesUID    series instance UID of the entry to be added
     *  @param  sopClassUID  SOP class UID of the entry to be added
     *  @param  instanceUID  SOP instance UID of the entry to be added
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition addItem(const OFString &studyUID,
                        const OFString &seriesUID,
                        const OFString &sopClassUID,
                        const OFString &instanceUID);

    /** add item from specified DICOM dataset to the list of references.
     *  Internally an item representing the given dataset is inserted into the hierarchical
     *  structure of studies, series and instances, if not already contained in the list.
     *  In any case the specified item is selected as the current one.
     ** @param  dataset  reference to DICOM dataset from which the relevant UIDs are retrieved
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition addItem(DcmItem &dataset);

    /** remove the current item from the list of referenced SOP instances.
     *  After successful removal the cursor is set to the next valid position.
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition removeItem();

    /** remove the specified item from the list of references.
     *  After successful removal the cursor is set to the next valid position.
     ** @param  sopClassUID  SOP class UID of the item to be removed
     *  @param  instanceUID  SOP instance UID of the item to be removed
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition removeItem(const OFString &sopClassUID,
                           const OFString &instanceUID);

    /** remove the specified item from the list of references.
     *  After successful removal the cursor is set to the next valid position.
     ** @param  studyUID     study instance UID of the item to be removed
     *  @param  seriesUID    series instance UID of the item to be removed
     *  @param  instanceUID  SOP instance UID of the item to be removed
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition removeItem(const OFString &studyUID,
                           const OFString &seriesUID,
                           const OFString &instanceUID);

    /** select the specified item as the current one
     ** @param  sopClassUID  SOP class UID of the item to be selected
     *  @param  instanceUID  SOP instance UID of the item to be selected
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition gotoItem(const OFString &sopClassUID,
                         const OFString &instanceUID);

    /** select the specified item as the current one
     ** @param  studyUID     study instance UID of the item to be selected
     *  @param  seriesUID    series instance UID of the item to be selected
     *  @param  instanceUID  SOP instance UID of the item to be selected
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition gotoItem(const OFString &studyUID,
                         const OFString &seriesUID,
                         const OFString &instanceUID);

    /** select the first item in the list.
     *  That means the first instance in the first series of the first study
     *  is selected (if available).
     ** @return status, EC_Normal if successful, an error code otherwise.
     *    (e.g. if the list is empty)
     */
    OFCondition gotoFirstItem();

    /** select the next item in the list.
     *  That means the next instance in the current series, or the first instance
     *  in the next series, or the first instance in the first series of the next
     *  study is selected (if available).  The combination of this function and
     *  gotoFirstItem() allows to iterate over all referenced SOP instances.
     ** @return status, EC_Normal if successful, an error code otherwise.
     *    (e.g. if the end of the list has been reached)
     */
    OFCondition gotoNextItem();

    /** get the study instance UID of the currently selected entry
     ** @param  stringValue  reference to string variable in which the result is stored
     ** @return reference to the resulting string (might be empty)
     */
    const OFString &getStudyInstanceUID(OFString &stringValue) const;

    /** get the series instance UID of the currently selected entry
     ** @param  stringValue  reference to string variable in which the result is stored
     ** @return reference to the resulting string (might be empty)
     */
    const OFString &getSeriesInstanceUID(OFString &stringValue) const;

    /** get the SOP instance UID of the currently selected entry
     ** @param  stringValue  reference to string variable in which the result is stored
     ** @return reference to the resulting string (might be empty)
     */
    const OFString &getSOPInstanceUID(OFString &stringValue) const;

    /** get the SOP class UID of the currently selected entry
     ** @param  stringValue  reference to string variable in which the result is stored
     ** @return reference to the resulting string (might be empty)
     */
    const OFString &getSOPClassUID(OFString &stringValue) const;

    /** get the retrieve application entity title of the currently selected entry (optional).
     *  The resulting string may contain multiple values separated by a backslash ("\").
     ** @param  stringValue  reference to string variable in which the result is stored
     ** @return reference to the resulting string (might be empty)
     */
    const OFString &getRetrieveAETitle(OFString &stringValue) const;

    /** get the storage media file set ID of the currently selected entry (optional)
     ** @param  stringValue  reference to string variable in which the result is stored
     ** @return reference to the resulting string (might be empty)
     */
    const OFString &getStorageMediaFileSetID(OFString &stringValue) const;

    /** get the storage media file set UID of the currently selected entry (optional)
     ** @param  stringValue  reference to string variable in which the result is stored
     ** @return reference to the resulting string (might be empty)
     */
    const OFString &getStorageMediaFileSetUID(OFString &stringValue) const;

    /** get purpose of reference code of the currently selected entry (optional)
     ** @param  codeValue  variable where a copy of the code should be stored
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition getPurposeOfReference(DSRCodedEntryValue &codeValue) const;

    /** set the retrieve application entity title of the currently selected entry.
     *  Multiple values are to be separated by a backslash ("\").
     ** @param  value  string value to be set (use empty string to omit optional attribute)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition setRetrieveAETitle(const OFString &value);

    /** set the storage media file set ID of the currently selected entry
     ** @param  value  string value to be set (use empty string to omit optional attribute)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition setStorageMediaFileSetID(const OFString &value);

    /** set the storage media file set UID of the currently selected entry
     ** @param  value  string value to be set (use empty string to omit optional attribute)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition setStorageMediaFileSetUID(const OFString &value);

    /** set purpose of reference code of the currently selected entry
     ** @param  codeValue  value to be set (use empty code to omit optional attribute)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    OFCondition setPurposeOfReference(const DSRCodedEntryValue &codeValue);


  protected:

    /** set cursor to the specified study entry (if existent)
     ** @param  studyUID  study instance UID of the entry to be searched for
     ** @return pointer to the study structure if successful, NULL otherwise
     */
    StudyStruct *gotoStudy(const OFString &studyUID);

    /** get pointer to currently selected study structure (if any)
     ** @return pointer to the study structure if successful, NULL otherwise
     */
    StudyStruct *getCurrentStudy() const;

    /** get pointer to currently selected series structure (if any)
     ** @return pointer to the series structure if successful, NULL otherwise
     */
    SeriesStruct *getCurrentSeries() const;

    /** get pointer to currently selected instance structure (if any)
     ** @return pointer to the instance structure if successful, NULL otherwise
     */
    InstanceStruct *getCurrentInstance() const;

    /** remove empty/incomplete items from the list.
     *  (e.g. series with no instances or studies with no series)
     *  Please note that this function modifies the value of 'Iterator'.
     */
    void removeIncompleteItems();


  private:

    /// DICOM tag specifying the attribute (sequence) of the reference list
    const DcmTagKey SequenceTag;

    /// list of studies
    OFList<StudyStruct *> StudyList;
    /// internal cursor to current (selected) list item
    OFListIterator(StudyStruct *) Iterator;

    // default constructor - not implemented!
    DSRSOPInstanceReferenceList();
    // copy constructor - not implemented!
    DSRSOPInstanceReferenceList(const DSRSOPInstanceReferenceList &);
    // assignment operator - not implemented!
    DSRSOPInstanceReferenceList &operator=(const DSRSOPInstanceReferenceList &);
};


#endif


/*
 *  CVS/RCS Log:
 *  $Log: dsrsoprf.h,v $
 *  Revision 1.18  2012-01-06 09:13:11  uli
 *  Make it possible to build dcmsr as a DLL.
 *
 *  Revision 1.17  2011-12-09 16:04:42  joergr
 *  Added support for optional Purpose of Reference Code Sequence (0040,A170) to
 *  class DSRSOPInstanceReferenceList.
 *
 *  Revision 1.16  2011-08-02 06:26:32  joergr
 *  Fixed typos and/or minor formatting issues.
 *
 *  Revision 1.15  2010-10-14 13:16:33  joergr
 *  Updated copyright header. Added reference to COPYRIGHT file.
 *
 *  Revision 1.14  2010-02-22 11:39:55  uli
 *  Remove some unneeded includes.
 *
 *  Revision 1.13  2009-10-13 14:57:50  uli
 *  Switched to logging mechanism provided by the "new" oflog module.
 *
 *  Revision 1.12  2007-11-15 16:33:19  joergr
 *  Fixed coding style to be more consistent.
 *
 *  Revision 1.11  2006/08/15 16:40:03  meichel
 *  Updated the code in module dcmsr to correctly compile when
 *    all standard C++ classes remain in namespace std.
 *
 *  Revision 1.10  2006/05/11 09:18:21  joergr
 *  Moved containsExtendedCharacters() from dcmsr to dcmdata module.
 *
 *  Revision 1.9  2005/12/08 16:05:18  meichel
 *  Changed include path schema for all DCMTK header files
 *
 *  Revision 1.8  2005/07/27 16:33:39  joergr
 *  Added method that allows to add a DICOM dataset to the list of references.
 *
 *  Revision 1.7  2004/11/22 16:39:09  meichel
 *  Added method that checks if the SR document contains non-ASCII characters
 *    in any of the strings affected by SpecificCharacterSet.
 *
 *  Revision 1.6  2003/08/07 18:01:42  joergr
 *  Removed libxml dependency from header files.
 *
 *  Revision 1.5  2003/08/07 12:50:12  joergr
 *  Added readXML functionality.
 *  Renamed parameters/variables "string" to avoid name clash with STL class.
 *  Enhanced class DSRSOPInstanceReferenceList: empty/incomplete items (e.g.
 *  series with no instances or studies with no series) are automatically
 *  removed from the list.
 *
 *  Revision 1.4  2002/08/30 14:16:59  joergr
 *  Removed "friend" statements from class declaration and moved sub-classes to
 *  the "public" section (required for Sun CC 6).
 *
 *  Revision 1.3  2002/05/14 08:16:07  joergr
 *  Added removeItem() methods.
 *
 *  Revision 1.2  2002/05/07 14:04:44  joergr
 *  Added "friend" statements to class declaration (required for MSVC).
 *
 *  Revision 1.1  2002/05/07 12:49:31  joergr
 *  Added support for the Current Requested Procedure Evidence Sequence and the
 *  Pertinent Other Evidence Sequence to the dcmsr module.
 *
 *
 */
