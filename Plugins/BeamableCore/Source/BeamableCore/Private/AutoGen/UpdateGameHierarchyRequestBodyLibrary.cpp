
#include "BeamableCore/Public/AutoGen/UpdateGameHierarchyRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUpdateGameHierarchyRequestBodyLibrary::UpdateGameHierarchyRequestBodyToJsonString(const UUpdateGameHierarchyRequestBody* Serializable, const bool Pretty)
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

UUpdateGameHierarchyRequestBody* UUpdateGameHierarchyRequestBodyLibrary::Make(FBeamPid RootPID, TArray<UProjectView*> Projects, UObject* Outer)
{
	auto Serializable = NewObject<UUpdateGameHierarchyRequestBody>(Outer);
	Serializable->RootPID = RootPID;
	Serializable->Projects = Projects;
	
	return Serializable;
}

void UUpdateGameHierarchyRequestBodyLibrary::Break(const UUpdateGameHierarchyRequestBody* Serializable, FBeamPid& RootPID, TArray<UProjectView*>& Projects)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		RootPID = Serializable->RootPID;
		Projects = Serializable->Projects;
	}
		
}

