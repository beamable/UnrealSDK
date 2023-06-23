
#include "BeamableCore/Public/AutoGen/ProjectViewLibrary.h"

#include "CoreMinimal.h"


FString UProjectViewLibrary::ProjectViewToJsonString(const UProjectView* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UProjectView* UProjectViewLibrary::Make(FString ProjectName, FBeamPid Pid, FOptionalBool bArchived, FOptionalBool bSharded, FOptionalString Secret, FOptionalBeamPid Parent, FOptionalBeamPid Children, FOptionalBeamCid Cid, UObject* Outer)
{
	auto Serializable = NewObject<UProjectView>(Outer);
	Serializable->ProjectName = ProjectName;
	Serializable->Pid = Pid;
	Serializable->bArchived = bArchived;
	Serializable->bSharded = bSharded;
	Serializable->Secret = Secret;
	Serializable->Parent = Parent;
	Serializable->Children = Children;
	Serializable->Cid = Cid;
	
	return Serializable;
}

void UProjectViewLibrary::Break(const UProjectView* Serializable, FString& ProjectName, FBeamPid& Pid, FOptionalBool& bArchived, FOptionalBool& bSharded, FOptionalString& Secret, FOptionalBeamPid& Parent, FOptionalBeamPid& Children, FOptionalBeamCid& Cid)
{
	ProjectName = Serializable->ProjectName;
	Pid = Serializable->Pid;
	bArchived = Serializable->bArchived;
	bSharded = Serializable->bSharded;
	Secret = Serializable->Secret;
	Parent = Serializable->Parent;
	Children = Serializable->Children;
	Cid = Serializable->Cid;
		
}

