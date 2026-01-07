#ifdef  _WINDOWS_SOURCE
#ifdef  __TrainModule
#define ExportedByTrainModule     __declspec(dllexport)
#else
#define ExportedByTrainModule     __declspec(dllimport)
#endif
#else
#define ExportedByTrainModule
#endif
