
#include "BeamableCore/Public/AutoGen/AliasAvailableResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAliasAvailableResponseLibrary::AliasAvailableResponseToJsonString(const UAliasAvailableResponse* Serializable, const bool Pretty)
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

UAliasAvailableResponse* UAliasAvailableResponseLibrary::Make(FString Alias, bool bAvailable, FBeamCid Cid, UObject* Outer)
{
	auto Serializable = NewObject<UAliasAvailableResponse>(Outer);
	Serializable->Alias = Alias;
	Serializable->bAvailable = bAvailable;
	Serializable->Cid = Cid;
	
	return Serializable;
}

void UAliasAvailableResponseLibrary::Break(const UAliasAvailableResponse* Serializable, FString& Alias, bool& bAvailable, FBeamCid& Cid)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Alias = Serializable->Alias;
		bAvailable = Serializable->bAvailable;
		Cid = Serializable->Cid;
	}
		
}

