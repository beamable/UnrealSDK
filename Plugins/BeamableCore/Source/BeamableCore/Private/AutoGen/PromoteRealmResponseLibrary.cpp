
#include "BeamableCore/Public/AutoGen/PromoteRealmResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPromoteRealmResponseLibrary::PromoteRealmResponseToJsonString(const UPromoteRealmResponse* Serializable, const bool Pretty)
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

UPromoteRealmResponse* UPromoteRealmResponseLibrary::Make(FBeamPid SourcePid, TArray<UPromotionScope*> Scopes, UObject* Outer)
{
	auto Serializable = NewObject<UPromoteRealmResponse>(Outer);
	Serializable->SourcePid = SourcePid;
	Serializable->Scopes = Scopes;
	
	return Serializable;
}

void UPromoteRealmResponseLibrary::Break(const UPromoteRealmResponse* Serializable, FBeamPid& SourcePid, TArray<UPromotionScope*>& Scopes)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SourcePid = Serializable->SourcePid;
		Scopes = Serializable->Scopes;
	}
		
}

