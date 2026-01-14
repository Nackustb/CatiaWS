#ifdef  _WINDOWS_SOURCE
#ifdef  __ExtractFeatureM
#define ExportedByExtractFeatureM     __declspec(dllexport)
#else
#define ExportedByExtractFeatureM     __declspec(dllimport)
#endif
#else
#define ExportedByExtractFeatureM
#endif
