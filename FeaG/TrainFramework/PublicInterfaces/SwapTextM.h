#ifdef  _WINDOWS_SOURCE
#ifdef  __SwapTextM
#define ExportedBySwapTextM     __declspec(dllexport)
#else
#define ExportedBySwapTextM     __declspec(dllimport)
#endif
#else
#define ExportedBySwapTextM
#endif
