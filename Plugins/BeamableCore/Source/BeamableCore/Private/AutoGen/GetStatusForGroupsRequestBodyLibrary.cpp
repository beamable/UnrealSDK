
#include "BeamableCore/Public/AutoGen/GetStatusForGroupsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetStatusForGroupsRequestBodyLibrary::GetStatusForGroupsRequestBodyToJsonString(const UGetStatusForGroupsRequestBody* Serializable, const bool Pretty)
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

UGetStatusForGroupsRequestBody* UGetStatusForGroupsRequestBodyLibrary::Make(FString ContentId, TArray<int64> GroupIds, UObject* Outer)
{
	auto Serializable = NewObject<UGetStatusForGroupsRequestBody>(Outer);
	Serializable->ContentId = ContentId;
	Serializable->GroupIds = GroupIds;
	
	return Serializable;
}

void UGetStatusForGroupsRequestBodyLibrary::Break(const UGetStatusForGroupsRequestBody* Serializable, FString& ContentId, TArray<int64>& GroupIds)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ContentId = Serializable->ContentId;
		GroupIds = Serializable->GroupIds;
	}
		
}

