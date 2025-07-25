
#include "BeamableCore/Public/AutoGen/GetGameResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetGameResponseLibrary::GetGameResponseToJsonString(const UGetGameResponse* Serializable, const bool Pretty)
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

UGetGameResponse* UGetGameResponseLibrary::Make(TArray<UProjectView*> Projects, UObject* Outer)
{
	auto Serializable = NewObject<UGetGameResponse>(Outer);
	Serializable->Projects = Projects;
	
	return Serializable;
}

void UGetGameResponseLibrary::Break(const UGetGameResponse* Serializable, TArray<UProjectView*>& Projects)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Projects = Serializable->Projects;
	}
		
}

