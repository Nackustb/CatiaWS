#ifdef  _WINDOWS_SOURCE
#ifdef  __TrainModuleCmd
#define ExportedByTrainModuleCmd     __declspec(dllexport)
#else
#define ExportedByTrainModuleCmd     __declspec(dllimport)
#endif
#else
#define ExportedByTrainModuleCmd
#endif
