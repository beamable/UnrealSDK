
#include "BeamableCore/Public/AutoGen/GamerTagAssociationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGamerTagAssociationLibrary::GamerTagAssociationToJsonString(const UGamerTagAssociation* Serializable, const bool Pretty)
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

UGamerTagAssociation* UGamerTagAssociationLibrary::Make(FBeamPid ProjectId, FBeamGamerTag GamerTag, UObject* Outer)
{
	auto Serializable = NewObject<UGamerTagAssociation>(Outer);
	Serializable->ProjectId = ProjectId;
	Serializable->GamerTag = GamerTag;
	
	return Serializable;
}

void UGamerTagAssociationLibrary::Break(const UGamerTagAssociation* Serializable, FBeamPid& ProjectId, FBeamGamerTag& GamerTag)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ProjectId = Serializable->ProjectId;
		GamerTag = Serializable->GamerTag;
	}
		
}

