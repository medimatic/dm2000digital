/* CIN source file */

#include "extcode.h"

/* lv_prolog.h and lv_epilog.h set up the correct alignment for LabVIEW data. */
#include "lv_prolog.h"

/* Typedefs */

typedef struct {
	int32 left;
	int32 top;
	int32 right;
	int32 bottom;
	} TD1;

typedef struct {
	int32 dimSize;
	uInt8 elt[1];
	} TD2;
typedef TD2 **TD2Hdl;

typedef struct {
	int32 dimSize;
	uInt32 elt[1];
	} TD3;
typedef TD3 **TD3Hdl;

#include "lv_epilog.h"

MgErr CINRun(uInt8 *imageDepth, TD1 *Input, TD2Hdl image, int32 *errCode, 
	TD3Hdl colors);

MgErr CINRun(uInt8 *imageDepth, TD1 *Input, TD2Hdl image, int32 *errCode, 
	TD3Hdl colors)
	{

	/* Insert code here */

	return noErr;
	}