
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/IncrementStatRequestArgsLibrary.h"

#include "CoreMinimal.h"


FString UIncrementStatRequestArgsLibrary::IncrementStatRequestArgsToJsonString(const UIncrementStatRequestArgs* Serializable, const bool Pretty)
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

UIncrementStatRequestArgs* UIncrementStatRequestArgsLibrary::Make(int64 GamerTag, UObject* Outer)
{
	auto Serializable = NewObject<UIncrementStatRequestArgs>(Outer);
	Serializable->GamerTag = GamerTag;
	
	return Serializable;
}

void UIncrementStatRequestArgsLibrary::Break(const UIncrementStatRequestArgs* Serializable, int64& GamerTag)
{
	GamerTag = Serializable->GamerTag;
		
}

