
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/UpgradeItemRequestArgsLibrary.h"

#include "CoreMinimal.h"


FString UUpgradeItemRequestArgsLibrary::UpgradeItemRequestArgsToJsonString(const UUpgradeItemRequestArgs* Serializable, const bool Pretty)
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

UUpgradeItemRequestArgs* UUpgradeItemRequestArgsLibrary::Make(int64 GamerTag, int64 ItemInstaceID, UObject* Outer)
{
	auto Serializable = NewObject<UUpgradeItemRequestArgs>(Outer);
	Serializable->GamerTag = GamerTag;
	Serializable->ItemInstaceID = ItemInstaceID;
	
	return Serializable;
}

void UUpgradeItemRequestArgsLibrary::Break(const UUpgradeItemRequestArgs* Serializable, int64& GamerTag, int64& ItemInstaceID)
{
	GamerTag = Serializable->GamerTag;
	ItemInstaceID = Serializable->ItemInstaceID;
		
}

