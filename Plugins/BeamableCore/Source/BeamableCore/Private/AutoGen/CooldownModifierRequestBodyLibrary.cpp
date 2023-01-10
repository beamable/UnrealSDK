
#include "AutoGen/CooldownModifierRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UCooldownModifierRequestBodyLibrary::CooldownModifierRequestBodyToJsonString(const UCooldownModifierRequestBody* Serializable, const bool Pretty)
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

UCooldownModifierRequestBody* UCooldownModifierRequestBodyLibrary::Make(int64 GamerTag, TArray<UUpdateListingCooldownRequestBody*> UpdateListingCooldownRequests, UObject* Outer)
{
	auto Serializable = NewObject<UCooldownModifierRequestBody>(Outer);
	Serializable->GamerTag = GamerTag;
	Serializable->UpdateListingCooldownRequests = UpdateListingCooldownRequests;
	
	return Serializable;
}

void UCooldownModifierRequestBodyLibrary::Break(const UCooldownModifierRequestBody* Serializable, int64& GamerTag, TArray<UUpdateListingCooldownRequestBody*>& UpdateListingCooldownRequests)
{
	GamerTag = Serializable->GamerTag;
	UpdateListingCooldownRequests = Serializable->UpdateListingCooldownRequests;
		
}
