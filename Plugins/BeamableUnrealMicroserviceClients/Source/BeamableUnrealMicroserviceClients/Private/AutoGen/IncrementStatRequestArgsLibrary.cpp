
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

UIncrementStatRequestArgs* UIncrementStatRequestArgsLibrary::Make(int64 UserID, UObject* Outer)
{
	auto Serializable = NewObject<UIncrementStatRequestArgs>(Outer);
	Serializable->UserID = UserID;
	
	return Serializable;
}

void UIncrementStatRequestArgsLibrary::Break(const UIncrementStatRequestArgs* Serializable, int64& UserID)
{
	UserID = Serializable->UserID;
		
}

