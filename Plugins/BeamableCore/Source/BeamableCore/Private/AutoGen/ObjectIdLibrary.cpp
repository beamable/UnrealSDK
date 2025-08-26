
#include "BeamableCore/Public/AutoGen/ObjectIdLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UObjectIdLibrary::ObjectIdToJsonString(const UObjectId* Serializable, const bool Pretty)
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

UObjectId* UObjectIdLibrary::Make(FOptionalInt32 Timestamp, FOptionalDateTime CreationTime, UObject* Outer)
{
	auto Serializable = NewObject<UObjectId>(Outer);
	Serializable->Timestamp = Timestamp;
	Serializable->CreationTime = CreationTime;
	
	return Serializable;
}

void UObjectIdLibrary::Break(const UObjectId* Serializable, FOptionalInt32& Timestamp, FOptionalDateTime& CreationTime)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Timestamp = Serializable->Timestamp;
		CreationTime = Serializable->CreationTime;
	}
		
}

