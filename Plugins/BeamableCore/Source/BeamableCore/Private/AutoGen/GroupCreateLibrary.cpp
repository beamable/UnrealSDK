
#include "BeamableCore/Public/AutoGen/GroupCreateLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGroupCreateLibrary::GroupCreateToJsonString(const UGroupCreate* Serializable, const bool Pretty)
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

UGroupCreate* UGroupCreateLibrary::Make(FString Name, FString EnrollmentType, int64 Requirement, EBeamGroupType Type, int32 MaxSize, FOptionalString Tag, FOptionalString ClientData, FOptionalInt64 Time, FOptionalInt64 Group, FOptionalArrayOfGroupScoreBinding Scores, UObject* Outer)
{
	auto Serializable = NewObject<UGroupCreate>(Outer);
	Serializable->Name = Name;
	Serializable->EnrollmentType = EnrollmentType;
	Serializable->Requirement = Requirement;
	Serializable->Type = Type;
	Serializable->MaxSize = MaxSize;
	Serializable->Tag = Tag;
	Serializable->ClientData = ClientData;
	Serializable->Time = Time;
	Serializable->Group = Group;
	Serializable->Scores = Scores;
	
	return Serializable;
}

void UGroupCreateLibrary::Break(const UGroupCreate* Serializable, FString& Name, FString& EnrollmentType, int64& Requirement, EBeamGroupType& Type, int32& MaxSize, FOptionalString& Tag, FOptionalString& ClientData, FOptionalInt64& Time, FOptionalInt64& Group, FOptionalArrayOfGroupScoreBinding& Scores)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		EnrollmentType = Serializable->EnrollmentType;
		Requirement = Serializable->Requirement;
		Type = Serializable->Type;
		MaxSize = Serializable->MaxSize;
		Tag = Serializable->Tag;
		ClientData = Serializable->ClientData;
		Time = Serializable->Time;
		Group = Serializable->Group;
		Scores = Serializable->Scores;
	}
		
}

