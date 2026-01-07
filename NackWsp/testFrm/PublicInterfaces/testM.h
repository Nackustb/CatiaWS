#ifdef  _WINDOWS_SOURCE
#ifdef  __testM
#define ExportedBytestM     __declspec(dllexport)
#else
#define ExportedBytestM     __declspec(dllimport)
#endif
#else
#define ExportedBytestM
#endif
