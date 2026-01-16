#ifdef  _WINDOWS_SOURCE
#ifdef  __CalculateAllowanceM
#define ExportedByCalculateAllowanceM     __declspec(dllexport)
#else
#define ExportedByCalculateAllowanceM     __declspec(dllimport)
#endif
#else
#define ExportedByCalculateAllowanceM
#endif
