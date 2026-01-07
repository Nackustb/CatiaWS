#ifdef  _WINDOWS_SOURCE
#ifdef  __AxisPointCmd
#define ExportedByAxisPointCmd     __declspec(dllexport)
#else
#define ExportedByAxisPointCmd     __declspec(dllimport)
#endif
#else
#define ExportedByAxisPointCmd
#endif
