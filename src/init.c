#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
 Check these declarations against the C/Fortran source code.
 */

/* .Call calls */
extern SEXP _GreedyEPL_p__CollapseLabelsCpp(SEXP);
extern SEXP _GreedyEPL_p__MinimiseAverageB(SEXP, SEXP, SEXP);
extern SEXP _GreedyEPL_p__MinimiseAverageNID(SEXP, SEXP, SEXP);
extern SEXP _GreedyEPL_p__MinimiseAverageNVI(SEXP, SEXP, SEXP);
extern SEXP _GreedyEPL_p__MinimiseAverageVI(SEXP, SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"_GreedyEPL_p__CollapseLabelsCpp",  (DL_FUNC) &_GreedyEPL_p__CollapseLabelsCpp,  1},
    {"_GreedyEPL_p__MinimiseAverageB",   (DL_FUNC) &_GreedyEPL_p__MinimiseAverageB,   3},
    {"_GreedyEPL_p__MinimiseAverageNID", (DL_FUNC) &_GreedyEPL_p__MinimiseAverageNID, 3},
    {"_GreedyEPL_p__MinimiseAverageNVI", (DL_FUNC) &_GreedyEPL_p__MinimiseAverageNVI, 3},
    {"_GreedyEPL_p__MinimiseAverageVI",  (DL_FUNC) &_GreedyEPL_p__MinimiseAverageVI,  3},
    {NULL, NULL, 0}
};

void R_init_GreedyEPL(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}

/* TO GENERATE THIS FILE I HAVE USED:
 tools::package_native_routine_registration_skeleton(".")
 
 OR
 tools::package_native_routine_registration_skeleton(".", character_only = FALSE)
 */
