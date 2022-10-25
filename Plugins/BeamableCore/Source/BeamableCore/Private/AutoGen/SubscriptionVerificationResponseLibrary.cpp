
#include "AutoGen/SubscriptionVerificationResponseLibrary.h"

#include "CoreMinimal.h"


FString USubscriptionVerificationResponseLibrary::SubscriptionVerificationResponseToJsonString(const USubscriptionVerificationResponse* Serializable, const bool Pretty)
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

USubscriptionVerificationResponse* USubscriptionVerificationResponseLibrary::Make(FString HubChallenge, FString ContentType, UObject* Outer)
{
	auto Serializable = NewObject<USubscriptionVerificationResponse>(Outer);
	Serializable->HubChallenge = HubChallenge;
	Serializable->ContentType = ContentType;
	
	return Serializable;
}

void USubscriptionVerificationResponseLibrary::Break(const USubscriptionVerificationResponse* Serializable, FString& HubChallenge, FString& ContentType)
{
	HubChallenge = Serializable->HubChallenge;
	ContentType = Serializable->ContentType;
		
}

