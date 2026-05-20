
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MutationOutputLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMutationOutputLibrary::MutationOutputToJsonString(const UMutationOutput* Serializable, const bool Pretty)
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

UMutationOutput* UMutationOutputLibrary::Make(FString ItemContentId, int32 Quantity, UObject* Outer)
{
	auto Serializable = NewObject<UMutationOutput>(Outer);
	Serializable->ItemContentId = ItemContentId;
	Serializable->Quantity = Quantity;
	
	return Serializable;
}

void UMutationOutputLibrary::Break(const UMutationOutput* Serializable, FString& ItemContentId, int32& Quantity)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ItemContentId = Serializable->ItemContentId;
		Quantity = Serializable->Quantity;
	}
		
}

