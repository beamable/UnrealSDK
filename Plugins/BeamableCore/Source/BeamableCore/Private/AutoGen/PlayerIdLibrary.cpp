
#include "AutoGen/PlayerIdLibrary.h"

#include "CoreMinimal.h"


FString UPlayerIdLibrary::PlayerIdToJsonString(const UPlayerId* Serializable, const bool Pretty)
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

UPlayerId* UPlayerIdLibrary::Make(FString PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<UPlayerId>(Outer);
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void UPlayerIdLibrary::Break(const UPlayerId* Serializable, FString& PlayerId)
{
	PlayerId = Serializable->PlayerId;
		
}

