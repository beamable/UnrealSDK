
#include "BeamableCore/Public/AutoGen/StatClientSubscriptionDataLibrary.h"

#include "CoreMinimal.h"


FString UStatClientSubscriptionDataLibrary::StatClientSubscriptionDataToJsonString(const UStatClientSubscriptionData* Serializable, const bool Pretty)
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

UStatClientSubscriptionData* UStatClientSubscriptionDataLibrary::Make(int64 TargetGamerTag, TArray<FString> Keys, UObject* Outer)
{
	auto Serializable = NewObject<UStatClientSubscriptionData>(Outer);
	Serializable->TargetGamerTag = TargetGamerTag;
	Serializable->Keys = Keys;
	
	return Serializable;
}

void UStatClientSubscriptionDataLibrary::Break(const UStatClientSubscriptionData* Serializable, int64& TargetGamerTag, TArray<FString>& Keys)
{
	TargetGamerTag = Serializable->TargetGamerTag;
	Keys = Serializable->Keys;
		
}

