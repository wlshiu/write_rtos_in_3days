/*-----------------------------------------------------------------------------
 *      Name:         DV_Framework.h 
 *      Purpose:      Framework header
 *----------------------------------------------------------------------------
 *      Copyright(c) KEIL - An ARM Company
 *----------------------------------------------------------------------------*/
#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__

#include "RV_Typedefs.h"
#include "RV_Report.h"

/*-----------------------------------------------------------------------------
 * Test framework global definitions
 *----------------------------------------------------------------------------*/

/* Test case definition macro                                                 */
#define TCD(x, y) {x, #x, y}

/* Test case description structure                                            */
typedef struct __TestCase {
  void (*TestFunc)(void);             /* Test function                        */
  const char *TFName;                 /* Test function name string            */
  BOOL en;                            /* Test function enabled                */
} TEST_CASE;

/* Test suite description structure                                           */
typedef struct __TestSuite {
  const char *FileName;               /* Test module file name                */
  const char *Date;                   /* Compilation date                     */
  const char *Time;                   /* Compilation time                     */
  const char *ReportTitle;            /* Title or name of module under test   */
  void (*Init)(void);                 /* Init function callback               */
  
  uint32_t TCBaseNum;                 /* Base number for test case numbering  */
  TEST_CASE *TC;                      /* Array of test cases                  */
  uint32_t NumOfTC;                   /* Number of test cases (sz of TC array)*/

} TEST_SUITE;

/* Defined in user test module                                                */
extern TEST_SUITE ts;

#endif /* __FRAMEWORK_H__ */
