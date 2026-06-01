
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetGroundItemsResultLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetGroundItemsResultLibrary::GetGroundItemsResultToJsonString(const UGetGroundItemsResult* Serializable, const bool Pretty)
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

UGetGroundItemsResult* UGetGroundItemsResultLibrary::Make(bool bSuccess, FString Message, TArray<UGroundItemEntry*> Items, UObject* Outer)
{
	auto Serializable = NewObject<UGetGroundItemsResult>(Outer);
	Serializable->bSuccess = bSuccess;
	Serializable->Message = Message;
	Serializable->Items = Items;
	
	return Serializable;
}

void UGetGroundItemsResultLibrary::Break(const UGetGroundItemsResult* Serializable, bool& bSuccess, FString& Message, TArray<UGroundItemEntry*>& Items)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bSuccess = Serializable->bSuccess;
		Message = Serializable->Message;
		Items = Serializable->Items;
	}
		
}

