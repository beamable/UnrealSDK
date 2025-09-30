
#include "BeamableCore/Public/AutoGen/RealmsBasicUpdateGameHierarchyRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmsBasicUpdateGameHierarchyRequestBodyLibrary::RealmsBasicUpdateGameHierarchyRequestBodyToJsonString(const URealmsBasicUpdateGameHierarchyRequestBody* Serializable, const bool Pretty)
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

URealmsBasicUpdateGameHierarchyRequestBody* URealmsBasicUpdateGameHierarchyRequestBodyLibrary::Make(FBeamPid RootPID, TArray<UProjectView*> Projects, UObject* Outer)
{
	auto Serializable = NewObject<URealmsBasicUpdateGameHierarchyRequestBody>(Outer);
	Serializable->RootPID = RootPID;
	Serializable->Projects = Projects;
	
	return Serializable;
}

void URealmsBasicUpdateGameHierarchyRequestBodyLibrary::Break(const URealmsBasicUpdateGameHierarchyRequestBody* Serializable, FBeamPid& RootPID, TArray<UProjectView*>& Projects)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		RootPID = Serializable->RootPID;
		Projects = Serializable->Projects;
	}
		
}

