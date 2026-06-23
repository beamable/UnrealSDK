
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeliveryRequirementLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UDeliveryRequirementLibrary::DeliveryRequirementToJsonString(const UDeliveryRequirement* Serializable, const bool Pretty)
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

UDeliveryRequirement* UDeliveryRequirementLibrary::Make(FString PropertyName, FString Comparison, int32 Value, UObject* Outer)
{
	auto Serializable = NewObject<UDeliveryRequirement>(Outer);
	Serializable->PropertyName = PropertyName;
	Serializable->Comparison = Comparison;
	Serializable->Value = Value;
	
	return Serializable;
}

void UDeliveryRequirementLibrary::Break(const UDeliveryRequirement* Serializable, FString& PropertyName, FString& Comparison, int32& Value)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PropertyName = Serializable->PropertyName;
		Comparison = Serializable->Comparison;
		Value = Serializable->Value;
	}
		
}

