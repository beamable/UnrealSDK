
#include "BeamableCore/Public/AutoGen/UnarchiveProjectRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUnarchiveProjectRequestBodyLibrary::UnarchiveProjectRequestBodyToJsonString(const UUnarchiveProjectRequestBody* Serializable, const bool Pretty)
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

UUnarchiveProjectRequestBody* UUnarchiveProjectRequestBodyLibrary::Make(FBeamPid ProjectId, UObject* Outer)
{
	auto Serializable = NewObject<UUnarchiveProjectRequestBody>(Outer);
	Serializable->ProjectId = ProjectId;
	
	return Serializable;
}

void UUnarchiveProjectRequestBodyLibrary::Break(const UUnarchiveProjectRequestBody* Serializable, FBeamPid& ProjectId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ProjectId = Serializable->ProjectId;
	}
		
}

