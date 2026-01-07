#ifdef  _WINDOWS_SOURCE
#ifdef  __testAddinM
#define ExportedBytestAddinM     __declspec(dllexport)
#else
#define ExportedBytestAddinM     __declspec(dllimport)
#endif
#else
#define ExportedBytestAddinM
#endif
