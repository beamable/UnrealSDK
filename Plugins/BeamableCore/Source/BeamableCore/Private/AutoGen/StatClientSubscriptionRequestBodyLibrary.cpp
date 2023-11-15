
#include "BeamableCore/Public/AutoGen/StatClientSubscriptionRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UStatClientSubscriptionRequestBodyLibrary::StatClientSubscriptionRequestBodyToJsonString(const UStatClientSubscriptionRequestBody* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UStatClientSubscriptionRequestBody* UStatClientSubscriptionRequestBodyLibrary::Make(FBeamGamerTag TargetGamerTag, TArray<FString> Keys, UObject* Outer)
{
	auto Serializable = NewObject<UStatClientSubscriptionRequestBody>(Outer);
	Serializable->TargetGamerTag = TargetGamerTag;
	Serializable->Keys = Keys;
	
	return Serializable;
}

void UStatClientSubscriptionRequestBodyLibrary::Break(const UStatClientSubscriptionRequestBody* Serializable, FBeamGamerTag& TargetGamerTag, TArray<FString>& Keys)
{
	TargetGamerTag = Serializable->TargetGamerTag;
	Keys = Serializable->Keys;
		
}

