
#include "BeamableCore/Public/AutoGen/GroupSearchResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGroupSearchResponseLibrary::GroupSearchResponseToJsonString(const UGroupSearchResponse* Serializable, const bool Pretty)
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

UGroupSearchResponse* UGroupSearchResponseLibrary::Make(TArray<UGroup*> Groups, UObject* Outer)
{
	auto Serializable = NewObject<UGroupSearchResponse>(Outer);
	Serializable->Groups = Groups;
	
	return Serializable;
}

void UGroupSearchResponseLibrary::Break(const UGroupSearchResponse* Serializable, TArray<UGroup*>& Groups)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Groups = Serializable->Groups;
	}
		
}

