
#include "BeamableCore/Public/AutoGen/SetCustomerAliasRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USetCustomerAliasRequestBodyLibrary::SetCustomerAliasRequestBodyToJsonString(const USetCustomerAliasRequestBody* Serializable, const bool Pretty)
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

USetCustomerAliasRequestBody* USetCustomerAliasRequestBodyLibrary::Make(FString Alias, UObject* Outer)
{
	auto Serializable = NewObject<USetCustomerAliasRequestBody>(Outer);
	Serializable->Alias = Alias;
	
	return Serializable;
}

void USetCustomerAliasRequestBodyLibrary::Break(const USetCustomerAliasRequestBody* Serializable, FString& Alias)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Alias = Serializable->Alias;
	}
		
}

