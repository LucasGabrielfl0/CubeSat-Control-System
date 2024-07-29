/**/

#define S_FUNCTION_NAME controle_digital
#define S_FUNCTION_LEVEL 2

#include "simstruc.h"
#include "math.h"

#ifndef MATLAB_MEX_FILE
#include <brtenv.h>
#endif

#define U(element) (*uPtrs[element])  /* Pointer to Input Port0 */












#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif