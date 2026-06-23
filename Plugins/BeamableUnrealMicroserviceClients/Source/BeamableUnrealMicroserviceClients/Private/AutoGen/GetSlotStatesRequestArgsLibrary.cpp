
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetSlotStatesRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetSlotStatesRequestArgsLibrary::GetSlotStatesRequestArgsToJsonString(const UGetSlotStatesRequestArgs* Serializable, const bool Pretty)
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

UGetSlotStatesRequestArgs* UGetSlotStatesRequestArgsLibrary::Make(TArray<FString> SlotIds, UObject* Outer)
{
	auto Serializable = NewObject<UGetSlotStatesRequestArgs>(Outer);
	Serializable->SlotIds = SlotIds;
	
	return Serializable;
}

void UGetSlotStatesRequestArgsLibrary::Break(const UGetSlotStatesRequestArgs* Serializable, TArray<FString>& SlotIds)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SlotIds = Serializable->SlotIds;
	}
		
}

