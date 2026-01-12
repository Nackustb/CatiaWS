#ifdef  _WINDOWS_SOURCE
#ifdef  __AddDocCmd
#define ExportedByAddDocCmd     __declspec(dllexport)
#else
#define ExportedByAddDocCmd     __declspec(dllimport)
#endif
#else
#define ExportedByAddDocCmd
#endif
