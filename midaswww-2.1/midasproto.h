/*
 * midasproto.h -- declarations of every external function in MidasWWW.
 *
 * Added for the 64-bit Linux port.  The original 1992 sources relied on
 * implicit "int" declarations for functions defined in other files.  On an
 * LP64 machine that silently truncates every pointer, Pixmap, XmString and
 * XtIntervalId returned by such a function to 32 bits, so every function is
 * declared here with its real return type.  Declarations deliberately use
 * empty parameter lists because the definitions are old-style (K&R) and
 * many of them take char/short/float arguments.
 */
#ifndef MIDASPROTO_H
#define MIDASPROTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include "midasoperand.h"

struct Ingot;
struct ConvertBlock;
struct ActionBlock;
struct _GIFImage;
struct MidasWidget;
struct _MidasShell;
struct _MidasApplication;
struct List;
struct ListItem;

void MidasError(char *format, ...);

Boolean GhostviewIsInterpreterReady();
Boolean GhostviewIsInterpreterRunning();
Boolean GhostviewNextPage();
Boolean GhostviewSendPS();
Boolean MidasConvertOperandInternal();
Boolean MidasConvertStringList();
Boolean MidasGetQualifier();
Boolean WWWAskForFileDestination();
Boolean XmuCvtStringToPageOrientation();
MidasOperand MidasApplyOperation();
MidasOperand MidasCallFunction();
MidasOperand MidasConvertFromBoolean();
MidasOperand MidasConvertFromInteger();
MidasOperand MidasConvertFromString();
MidasOperand MidasEvaluateExpression();
MidasOperand MidasGetAppResource();
MidasOperand MidasGetCallback();
MidasOperand MidasGetCreateCallback();
MidasOperand MidasGetIngot();
MidasOperand MidasGetIngotOption();
MidasOperand MidasGetIngotValue();
MidasOperand MidasGetValue();
MidasOperand MidasGetValueOwner();
MidasOperand MidasGetValueRaw();
MidasOperand MidasModifier();
MidasOperand WWWTempFile();
Pixmap GIFToPixmap();
Pixmap GhostviewGetBackingPixmap();
Pixmap MidasFetchIcon();
struct _SGMLTextRec *find_segment();
Widget *DXmChildren();
Widget ExtHiliteSelection();
Widget MidasCreateDialog();
Widget MidasCreateShell();
Widget MidasCreateWidget();
Widget MidasFetch();
Widget MidasFindWidget();
Widget MidasGetActiveWidget();
Widget MidasInitializeFallback();
Widget MidasInitializeUser();
Widget MidasScanWidgetTree();
Widget MidasTraceWidgetTree();
Widget SGMLCreateAnchorText();
Widget SGMLCreateCompositeText();
Widget SGMLCreateContainerText();
Widget SGMLCreateFormattedText();
Widget SGMLCreateHyper();
Widget SGMLCreateInputText();
Widget SGMLCreateListText();
Widget SGMLCreateMarkerText();
Widget SGMLCreatePlainText();
Widget SGMLCreateRuleText();
Widget SGMLCreateText();
Widget SGMLCreateWidget();
Widget SGMLHyperClose();
Widget SGMLHyperLoadFile();
Widget SGMLHyperLoadText();
Widget SGMLHyperSearch();
Widget SGMLHyperSetText();
Widget WWWFetchDocumentFTP();
Widget WWWFetchDocumentGOPHER();
Widget WWWFetchDocumentHTTP();
Widget WWWFetchDocumentHTTP1();
Widget WWWFetchDocumentLOCAL();
Widget WWWFetchDocumentTELNET();
Widget WWWLoadByFiletype();
Widget WWWLoadGIF();
Widget WWWLoadPS();
Widget WWWPostDocumentHTTP1();
XImage *GIFToXImage();
XmAnyCallbackStruct *MidasGetActiveCallback();
XmString MidasCharToString();
XtAppContext MidasInitialize();
XtPointer SGMLHyperOpen();
char *MidasConvertToBoolean();
char *MidasConvertToString();
char *MidasGetCallbackValue();
char *MidasGetWidgetName();
char *MidasQueryUser();
char *MidasStringToChar();
char *SGMLHyperGetText();
char *WWWAsciiFile();
char *WWWGetHTRQ();
int ExtTextWidth();
int GetCharacter();
int MidasConvertToInteger();
int MidasDeclareQualifier();
int MidasFindItemPosInList();
int MidasListInit();
int MidasMakeUid();
int TCPIPConnect();
int TCPIPWriteAndWaitForResponse();
int WWWWriteToTempfile();
struct ActionBlock *MidasPrepareToDispatch();
struct ConvertBlock *MidasFindStringConverter();
struct Ingot *MidasCreateIngot();
struct Ingot *MidasFindIngot();
struct Ingot *MidasFindIngotHere();
struct List *MidasCreateEmptyList();
struct ListItem *MidasAddItemToList();
struct ListItem *MidasAddItemToListPos();
struct ListItem *MidasFindItemInList();
struct ListItem *MidasFindItemInListPos();
struct MidasWidget *MidasWidgetToMW();
struct _GIFImage *GIFLoadFile();
struct _MidasApplication *MidasCreateApplication();
struct _MidasApplication *MidasGetApplication();
struct _MidasShell *MidasGetShell();
void CustomConnect();
void CustomCreate();
void CustomInit();
void CustomPopup();
void CustomReadSystem();
void CustomReadUser();
void CustomWriteUser();
void CvtStringToBullet();
void CvtStringToGravity();
void CvtStringToManagementPolicy();
void ExtDrawString();
void FreeFile();
void GIFFreeFile();
void GIFFreeImage();
void GhostviewDisableInterpreter();
void GhostviewEnableInterpreter();
void GhostviewLayout();
void MidasBeep();
void MidasClassInit();
void MidasClearWindow();
void MidasCloseUidFile();
void MidasConvertInit();
void MidasConvertOperand();
void MidasCopyList();
void MidasCreateWidgetTree();
void MidasDeclare();
void MidasDeclareClass();
void MidasDeclareConverter();
void MidasDeclareFunction();
void MidasDeclareInit();
void MidasDeclareStringConverter();
void MidasDeclareVerb();
void MidasDefaultWarningHandler();
void MidasDestroyApplication();
void MidasDestroyIngots();
void MidasDestroyList();
void MidasDestroyShell();
void MidasDispatchAndTrapErrors();
void MidasDispatchCommand();
void MidasDispatchCommandCallback();
void MidasDispatchQueuedCommands();
void MidasDummyHandler();
void MidasEchoCommand();
void MidasEmptyList();
void MidasFetchDispatchEvent();
void MidasFlush();
void MidasForceDialog();
void MidasForceEvaluateExpression();
void MidasGetCallbacks();
void MidasGetIngots();
void MidasGetResources();
void MidasIgnore();
void MidasInheritIngotValue();
void MidasInitializeIngots();
void MidasInvokeAction();
void MidasInvokeCallback();
void MidasLoadImage();
void MidasMainLoop();
void MidasPopup();
void MidasQueueCommand();
void MidasRealizeList();
void MidasReenableXtWarningMessages();
void MidasRemoveItemFromList();
void MidasScanAncestors();
void MidasScanChildren();
void MidasSelectItemPosInList();
void MidasSendActionProc();
void MidasSetCallback();
void MidasSetCallbackValue();
void MidasSetCursor();
void MidasSetIngot();
void MidasSetIngotOption();
void MidasSetIngotP();
void MidasSetIngotString();
void MidasSetIngotValue();
void MidasSetQualifier();
void MidasSetSensitive();
void MidasSetValue();
void MidasSetupIngots();
void MidasSetupWidget();
void MidasSpecialActionProc();
void MidasStartInterpreter();
void MidasSuppressXtWarningMessages();
void MidasSystem();
void MidasTokenizeCommand();
void MidasUnrealizeList();
void MidasUpdate();
void MidasUtilInit();
void MidasWidgetBeingDestroyed();
void SGMLCompositeTextDeleteChild();
void SGMLCompositeTextInsertChild();
void SGMLFormSetResult();
void SGMLHyperDeclareClass();
void SGMLHyperManageChild();
void SGMLHyperRedisplay();
void SGMLHyperSetTags();
void SGMLHyperShowObject();
void SGMLHyperWrite();
void SGMLHyperWriteData();
void TreeForceLayout();
void WWWFreeFiletype();
void WWWInitDataSource();
void WWWMidasInit();
void _SGMLBreak();
void check_passwd();
void fastAllocFreeUnusedColors();
void pscopy();
void psfree();

#endif /* MIDASPROTO_H */
