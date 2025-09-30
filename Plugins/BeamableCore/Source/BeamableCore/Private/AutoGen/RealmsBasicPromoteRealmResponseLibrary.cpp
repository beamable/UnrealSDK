
#include "BeamableCore/Public/AutoGen/RealmsBasicPromoteRealmResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmsBasicPromoteRealmResponseLibrary::RealmsBasicPromoteRealmResponseToJsonString(const URealmsBasicPromoteRealmResponse* Serializable, const bool Pretty)
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

URealmsBasicPromoteRealmResponse* URealmsBasicPromoteRealmResponseLibrary::Make(FBeamPid SourcePid, TArray<UPromotionScope*> Scopes, UObject* Outer)
{
	auto Serializable = NewObject<URealmsBasicPromoteRealmResponse>(Outer);
	Serializable->SourcePid = SourcePid;
	Serializable->Scopes = Scopes;
	
	return Serializable;
}

void URealmsBasicPromoteRealmResponseLibrary::Break(const URealmsBasicPromoteRealmResponse* Serializable, FBeamPid& SourcePid, TArray<UPromotionScope*>& Scopes)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SourcePid = Serializable->SourcePid;
		Scopes = Serializable->Scopes;
	}
		
}

