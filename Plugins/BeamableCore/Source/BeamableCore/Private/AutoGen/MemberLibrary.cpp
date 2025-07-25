
#include "BeamableCore/Public/AutoGen/MemberLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMemberLibrary::MemberToJsonString(const UMember* Serializable, const bool Pretty)
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

UMember* UMemberLibrary::Make(FString Role, int64 GamerTag, FOptionalBool bCanDemote, FOptionalBool bCanKick, FOptionalBool bCanPromote, FOptionalArrayOfGroupScoreBinding Scores, UObject* Outer)
{
	auto Serializable = NewObject<UMember>(Outer);
	Serializable->Role = Role;
	Serializable->GamerTag = GamerTag;
	Serializable->bCanDemote = bCanDemote;
	Serializable->bCanKick = bCanKick;
	Serializable->bCanPromote = bCanPromote;
	Serializable->Scores = Scores;
	
	return Serializable;
}

void UMemberLibrary::Break(const UMember* Serializable, FString& Role, int64& GamerTag, FOptionalBool& bCanDemote, FOptionalBool& bCanKick, FOptionalBool& bCanPromote, FOptionalArrayOfGroupScoreBinding& Scores)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Role = Serializable->Role;
		GamerTag = Serializable->GamerTag;
		bCanDemote = Serializable->bCanDemote;
		bCanKick = Serializable->bCanKick;
		bCanPromote = Serializable->bCanPromote;
		Scores = Serializable->Scores;
	}
		
}

