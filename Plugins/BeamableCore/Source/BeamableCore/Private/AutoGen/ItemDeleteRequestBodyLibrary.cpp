
#include "BeamableCore/Public/AutoGen/ItemDeleteRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UItemDeleteRequestBodyLibrary::ItemDeleteRequestBodyToJsonString(const UItemDeleteRequestBody* Serializable, const bool Pretty)
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

UItemDeleteRequestBody* UItemDeleteRequestBodyLibrary::Make(FString ContentId, int64 Id, UObject* Outer)
{
	auto Serializable = NewObject<UItemDeleteRequestBody>(Outer);
	Serializable->ContentId = ContentId;
	Serializable->Id = Id;
	
	return Serializable;
}

void UItemDeleteRequestBodyLibrary::Break(const UItemDeleteRequestBody* Serializable, FString& ContentId, int64& Id)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ContentId = Serializable->ContentId;
		Id = Serializable->Id;
	}
		
}

