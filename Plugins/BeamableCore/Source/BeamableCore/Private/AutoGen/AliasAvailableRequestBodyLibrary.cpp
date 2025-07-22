
#include "BeamableCore/Public/AutoGen/AliasAvailableRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAliasAvailableRequestBodyLibrary::AliasAvailableRequestBodyToJsonString(const UAliasAvailableRequestBody* Serializable, const bool Pretty)
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

UAliasAvailableRequestBody* UAliasAvailableRequestBodyLibrary::Make(FString Alias, UObject* Outer)
{
	auto Serializable = NewObject<UAliasAvailableRequestBody>(Outer);
	Serializable->Alias = Alias;
	
	return Serializable;
}

void UAliasAvailableRequestBodyLibrary::Break(const UAliasAvailableRequestBody* Serializable, FString& Alias)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Alias = Serializable->Alias;
	}
		
}

