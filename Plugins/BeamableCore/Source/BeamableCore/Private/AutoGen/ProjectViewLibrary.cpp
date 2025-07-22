
#include "BeamableCore/Public/AutoGen/ProjectViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UProjectViewLibrary::ProjectViewToJsonString(const UProjectView* Serializable, const bool Pretty)
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

UProjectView* UProjectViewLibrary::Make(FString ProjectName, FBeamPid Pid, FOptionalBool bArchived, FOptionalBool bSharded, FOptionalString Secret, FOptionalBeamPid Parent, FOptionalBeamCid Cid, FOptionalArrayOfBeamPid Children, UObject* Outer)
{
	auto Serializable = NewObject<UProjectView>(Outer);
	Serializable->ProjectName = ProjectName;
	Serializable->Pid = Pid;
	Serializable->bArchived = bArchived;
	Serializable->bSharded = bSharded;
	Serializable->Secret = Secret;
	Serializable->Parent = Parent;
	Serializable->Cid = Cid;
	Serializable->Children = Children;
	
	return Serializable;
}

void UProjectViewLibrary::Break(const UProjectView* Serializable, FString& ProjectName, FBeamPid& Pid, FOptionalBool& bArchived, FOptionalBool& bSharded, FOptionalString& Secret, FOptionalBeamPid& Parent, FOptionalBeamCid& Cid, FOptionalArrayOfBeamPid& Children)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ProjectName = Serializable->ProjectName;
		Pid = Serializable->Pid;
		bArchived = Serializable->bArchived;
		bSharded = Serializable->bSharded;
		Secret = Serializable->Secret;
		Parent = Serializable->Parent;
		Cid = Serializable->Cid;
		Children = Serializable->Children;
	}
		
}

