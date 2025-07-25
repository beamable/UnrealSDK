
#include "BeamableCore/Public/AutoGen/ContentLimitsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UContentLimitsLibrary::ContentLimitsToJsonString(const UContentLimits* Serializable, const bool Pretty)
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

UContentLimits* UContentLimitsLibrary::Make(FOptionalInt32 MaxDistinctContentIds, UObject* Outer)
{
	auto Serializable = NewObject<UContentLimits>(Outer);
	Serializable->MaxDistinctContentIds = MaxDistinctContentIds;
	
	return Serializable;
}

void UContentLimitsLibrary::Break(const UContentLimits* Serializable, FOptionalInt32& MaxDistinctContentIds)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		MaxDistinctContentIds = Serializable->MaxDistinctContentIds;
	}
		
}

