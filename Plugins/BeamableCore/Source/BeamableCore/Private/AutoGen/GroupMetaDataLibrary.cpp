
#include "BeamableCore/Public/AutoGen/GroupMetaDataLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGroupMetaDataLibrary::GroupMetaDataToJsonString(const UGroupMetaData* Serializable, const bool Pretty)
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

UGroupMetaData* UGroupMetaDataLibrary::Make(int64 Id, FOptionalString Name, FOptionalString Tag, UObject* Outer)
{
	auto Serializable = NewObject<UGroupMetaData>(Outer);
	Serializable->Id = Id;
	Serializable->Name = Name;
	Serializable->Tag = Tag;
	
	return Serializable;
}

void UGroupMetaDataLibrary::Break(const UGroupMetaData* Serializable, int64& Id, FOptionalString& Name, FOptionalString& Tag)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Name = Serializable->Name;
		Tag = Serializable->Tag;
	}
		
}

