
#include "BeamableCore/Public/AutoGen/ReplaceObjectsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UReplaceObjectsRequestBodyLibrary::ReplaceObjectsRequestBodyToJsonString(const UReplaceObjectsRequestBody* Serializable, const bool Pretty)
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

UReplaceObjectsRequestBody* UReplaceObjectsRequestBodyLibrary::Make(int64 SourcePlayerId, int64 TargetPlayerId, UObject* Outer)
{
	auto Serializable = NewObject<UReplaceObjectsRequestBody>(Outer);
	Serializable->SourcePlayerId = SourcePlayerId;
	Serializable->TargetPlayerId = TargetPlayerId;
	
	return Serializable;
}

void UReplaceObjectsRequestBodyLibrary::Break(const UReplaceObjectsRequestBody* Serializable, int64& SourcePlayerId, int64& TargetPlayerId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SourcePlayerId = Serializable->SourcePlayerId;
		TargetPlayerId = Serializable->TargetPlayerId;
	}
		
}

