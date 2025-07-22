
#include "BeamableCore/Public/AutoGen/ArchiveProjectRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UArchiveProjectRequestBodyLibrary::ArchiveProjectRequestBodyToJsonString(const UArchiveProjectRequestBody* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UArchiveProjectRequestBody* UArchiveProjectRequestBodyLibrary::Make(FBeamPid Pid, UObject* Outer)
{
	auto Serializable = NewObject<UArchiveProjectRequestBody>(Outer);
	Serializable->Pid = Pid;
	
	return Serializable;
}

void UArchiveProjectRequestBodyLibrary::Break(const UArchiveProjectRequestBody* Serializable, FBeamPid& Pid)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Pid = Serializable->Pid;
	}
		
}

