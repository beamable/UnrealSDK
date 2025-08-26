
#include "BeamableCore/Public/AutoGen/GroupUpdateLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGroupUpdateLibrary::GroupUpdateToJsonString(const UGroupUpdate* Serializable, const bool Pretty)
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

UGroupUpdate* UGroupUpdateLibrary::Make(FOptionalString Name, FOptionalString EnrollmentType, FOptionalString Tag, FOptionalString Slogan, FOptionalInt64 Requirement, FOptionalString Motd, FOptionalString ClientData, FOptionalInt64 SubGroup, UObject* Outer)
{
	auto Serializable = NewObject<UGroupUpdate>(Outer);
	Serializable->Name = Name;
	Serializable->EnrollmentType = EnrollmentType;
	Serializable->Tag = Tag;
	Serializable->Slogan = Slogan;
	Serializable->Requirement = Requirement;
	Serializable->Motd = Motd;
	Serializable->ClientData = ClientData;
	Serializable->SubGroup = SubGroup;
	
	return Serializable;
}

void UGroupUpdateLibrary::Break(const UGroupUpdate* Serializable, FOptionalString& Name, FOptionalString& EnrollmentType, FOptionalString& Tag, FOptionalString& Slogan, FOptionalInt64& Requirement, FOptionalString& Motd, FOptionalString& ClientData, FOptionalInt64& SubGroup)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		EnrollmentType = Serializable->EnrollmentType;
		Tag = Serializable->Tag;
		Slogan = Serializable->Slogan;
		Requirement = Serializable->Requirement;
		Motd = Serializable->Motd;
		ClientData = Serializable->ClientData;
		SubGroup = Serializable->SubGroup;
	}
		
}

