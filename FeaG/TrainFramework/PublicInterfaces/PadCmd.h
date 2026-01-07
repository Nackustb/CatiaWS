#ifdef  _WINDOWS_SOURCE
#ifdef  __PadCmd
#define ExportedByPadCmd     __declspec(dllexport)
#else
#define ExportedByPadCmd     __declspec(dllimport)
#endif
#else
#define ExportedByPadCmd
#endif
