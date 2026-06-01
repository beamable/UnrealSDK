
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetSlotStatesResultLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetSlotStatesResultLibrary::GetSlotStatesResultToJsonString(const UGetSlotStatesResult* Serializable, const bool Pretty)
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

UGetSlotStatesResult* UGetSlotStatesResultLibrary::Make(bool bSuccess, FString Message, TArray<USlotStateEntry*> Slots, UObject* Outer)
{
	auto Serializable = NewObject<UGetSlotStatesResult>(Outer);
	Serializable->bSuccess = bSuccess;
	Serializable->Message = Message;
	Serializable->Slots = Slots;
	
	return Serializable;
}

void UGetSlotStatesResultLibrary::Break(const UGetSlotStatesResult* Serializable, bool& bSuccess, FString& Message, TArray<USlotStateEntry*>& Slots)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bSuccess = Serializable->bSuccess;
		Message = Serializable->Message;
		Slots = Serializable->Slots;
	}
		
}

