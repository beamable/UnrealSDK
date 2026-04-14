
#include "BeamableCore/Public/AutoGen/AuthV2RefreshTokenResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2RefreshTokenResponseLibrary::AuthV2RefreshTokenResponseToJsonString(const UAuthV2RefreshTokenResponse* Serializable, const bool Pretty)
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

UAuthV2RefreshTokenResponse* UAuthV2RefreshTokenResponseLibrary::Make(FOptionalString Token, FOptionalDateTime Created, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2RefreshTokenResponse>(Outer);
	Serializable->Token = Token;
	Serializable->Created = Created;
	
	return Serializable;
}

void UAuthV2RefreshTokenResponseLibrary::Break(const UAuthV2RefreshTokenResponse* Serializable, FOptionalString& Token, FOptionalDateTime& Created)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Token = Serializable->Token;
		Created = Serializable->Created;
	}
		
}

