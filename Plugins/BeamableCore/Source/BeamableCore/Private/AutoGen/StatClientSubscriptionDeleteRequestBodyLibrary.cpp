
#include "BeamableCore/Public/AutoGen/StatClientSubscriptionDeleteRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UStatClientSubscriptionDeleteRequestBodyLibrary::StatClientSubscriptionDeleteRequestBodyToJsonString(const UStatClientSubscriptionDeleteRequestBody* Serializable, const bool Pretty)
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

UStatClientSubscriptionDeleteRequestBody* UStatClientSubscriptionDeleteRequestBodyLibrary::Make(FBeamGamerTag TargetGamerTag, TArray<FString> Keys, FOptionalBool bDeleteAll, UObject* Outer)
{
	auto Serializable = NewObject<UStatClientSubscriptionDeleteRequestBody>(Outer);
	Serializable->TargetGamerTag = TargetGamerTag;
	Serializable->Keys = Keys;
	Serializable->bDeleteAll = bDeleteAll;
	
	return Serializable;
}

void UStatClientSubscriptionDeleteRequestBodyLibrary::Break(const UStatClientSubscriptionDeleteRequestBody* Serializable, FBeamGamerTag& TargetGamerTag, TArray<FString>& Keys, FOptionalBool& bDeleteAll)
{
	TargetGamerTag = Serializable->TargetGamerTag;
	Keys = Serializable->Keys;
	bDeleteAll = Serializable->bDeleteAll;
		
}

