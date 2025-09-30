
#include "BeamableCore/Public/AutoGen/RealmsBasicAliasAvailableResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmsBasicAliasAvailableResponseLibrary::RealmsBasicAliasAvailableResponseToJsonString(const URealmsBasicAliasAvailableResponse* Serializable, const bool Pretty)
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

URealmsBasicAliasAvailableResponse* URealmsBasicAliasAvailableResponseLibrary::Make(FString Alias, bool bAvailable, FBeamCid Cid, UObject* Outer)
{
	auto Serializable = NewObject<URealmsBasicAliasAvailableResponse>(Outer);
	Serializable->Alias = Alias;
	Serializable->bAvailable = bAvailable;
	Serializable->Cid = Cid;
	
	return Serializable;
}

void URealmsBasicAliasAvailableResponseLibrary::Break(const URealmsBasicAliasAvailableResponse* Serializable, FString& Alias, bool& bAvailable, FBeamCid& Cid)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Alias = Serializable->Alias;
		bAvailable = Serializable->bAvailable;
		Cid = Serializable->Cid;
	}
		
}

