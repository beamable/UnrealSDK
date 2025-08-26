
#include "BeamableCore/Public/AutoGen/GroupSearchRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGroupSearchRequestBodyLibrary::GroupSearchRequestBodyToJsonString(const UGroupSearchRequestBody* Serializable, const bool Pretty)
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

UGroupSearchRequestBody* UGroupSearchRequestBodyLibrary::Make(EBeamGroupType Type, FOptionalBool bHasSlots, FOptionalBool bSubGroup, FOptionalString Name, FOptionalInt64 ScoreMin, FOptionalString SortField, FOptionalInt64 UserScore, FOptionalString EnrollmentTypes, FOptionalInt32 Offset, FOptionalInt64 ScoreMax, FOptionalInt32 SortValue, FOptionalInt32 Limit, UObject* Outer)
{
	auto Serializable = NewObject<UGroupSearchRequestBody>(Outer);
	Serializable->Type = Type;
	Serializable->bHasSlots = bHasSlots;
	Serializable->bSubGroup = bSubGroup;
	Serializable->Name = Name;
	Serializable->ScoreMin = ScoreMin;
	Serializable->SortField = SortField;
	Serializable->UserScore = UserScore;
	Serializable->EnrollmentTypes = EnrollmentTypes;
	Serializable->Offset = Offset;
	Serializable->ScoreMax = ScoreMax;
	Serializable->SortValue = SortValue;
	Serializable->Limit = Limit;
	
	return Serializable;
}

void UGroupSearchRequestBodyLibrary::Break(const UGroupSearchRequestBody* Serializable, EBeamGroupType& Type, FOptionalBool& bHasSlots, FOptionalBool& bSubGroup, FOptionalString& Name, FOptionalInt64& ScoreMin, FOptionalString& SortField, FOptionalInt64& UserScore, FOptionalString& EnrollmentTypes, FOptionalInt32& Offset, FOptionalInt64& ScoreMax, FOptionalInt32& SortValue, FOptionalInt32& Limit)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Type = Serializable->Type;
		bHasSlots = Serializable->bHasSlots;
		bSubGroup = Serializable->bSubGroup;
		Name = Serializable->Name;
		ScoreMin = Serializable->ScoreMin;
		SortField = Serializable->SortField;
		UserScore = Serializable->UserScore;
		EnrollmentTypes = Serializable->EnrollmentTypes;
		Offset = Serializable->Offset;
		ScoreMax = Serializable->ScoreMax;
		SortValue = Serializable->SortValue;
		Limit = Serializable->Limit;
	}
		
}

