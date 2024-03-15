
#include "BeamableCore/Public/AutoGen/GroupCreateResponseLibrary.h"

#include "CoreMinimal.h"


FString UGroupCreateResponseLibrary::GroupCreateResponseToJsonString(const UGroupCreateResponse* Serializable, const bool Pretty)
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

UGroupCreateResponse* UGroupCreateResponseLibrary::Make(UGroupMetaData* Group, UObject* Outer)
{
	auto Serializable = NewObject<UGroupCreateResponse>(Outer);
	Serializable->Group = Group;
	
	return Serializable;
}

void UGroupCreateResponseLibrary::Break(const UGroupCreateResponse* Serializable, UGroupMetaData*& Group)
{
	Group = Serializable->Group;
		
}

