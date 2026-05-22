
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MutationInputLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMutationInputLibrary::MutationInputToJsonString(const UMutationInput* Serializable, const bool Pretty)
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

UMutationInput* UMutationInputLibrary::Make(FString ItemContentId, int32 Quantity, UObject* Outer)
{
	auto Serializable = NewObject<UMutationInput>(Outer);
	Serializable->ItemContentId = ItemContentId;
	Serializable->Quantity = Quantity;
	
	return Serializable;
}

void UMutationInputLibrary::Break(const UMutationInput* Serializable, FString& ItemContentId, int32& Quantity)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ItemContentId = Serializable->ItemContentId;
		Quantity = Serializable->Quantity;
	}
		
}

