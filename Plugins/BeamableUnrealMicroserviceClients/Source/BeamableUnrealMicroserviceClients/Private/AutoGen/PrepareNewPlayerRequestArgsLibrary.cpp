
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PrepareNewPlayerRequestArgsLibrary.h"

#include "CoreMinimal.h"


FString UPrepareNewPlayerRequestArgsLibrary::PrepareNewPlayerRequestArgsToJsonString(const UPrepareNewPlayerRequestArgs* Serializable, const bool Pretty)
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

UPrepareNewPlayerRequestArgs* UPrepareNewPlayerRequestArgsLibrary::Make(int64 UserID, UObject* Outer)
{
	auto Serializable = NewObject<UPrepareNewPlayerRequestArgs>(Outer);
	Serializable->UserID = UserID;
	
	return Serializable;
}

void UPrepareNewPlayerRequestArgsLibrary::Break(const UPrepareNewPlayerRequestArgs* Serializable, int64& UserID)
{
	UserID = Serializable->UserID;
		
}

