#ifdef  _WINDOWS_SOURCE
#ifdef  __PointCmd
#define ExportedByPointCmd     __declspec(dllexport)
#else
#define ExportedByPointCmd     __declspec(dllimport)
#endif
#else
#define ExportedByPointCmd
#endif
