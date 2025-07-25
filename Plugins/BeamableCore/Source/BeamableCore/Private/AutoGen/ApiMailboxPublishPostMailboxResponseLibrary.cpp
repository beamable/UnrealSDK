
#include "BeamableCore/Public/AutoGen/ApiMailboxPublishPostMailboxResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UApiMailboxPublishPostMailboxResponseLibrary::ApiMailboxPublishPostMailboxResponseToJsonString(const UApiMailboxPublishPostMailboxResponse* Serializable, const bool Pretty)
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

UApiMailboxPublishPostMailboxResponse* UApiMailboxPublishPostMailboxResponseLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UApiMailboxPublishPostMailboxResponse>(Outer);
	
	return Serializable;
}



