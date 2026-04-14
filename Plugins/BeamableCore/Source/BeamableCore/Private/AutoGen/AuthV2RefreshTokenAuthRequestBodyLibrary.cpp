
#include "BeamableCore/Public/AutoGen/AuthV2RefreshTokenAuthRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2RefreshTokenAuthRequestBodyLibrary::AuthV2RefreshTokenAuthRequestBodyToJsonString(const UAuthV2RefreshTokenAuthRequestBody* Serializable, const bool Pretty)
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

UAuthV2RefreshTokenAuthRequestBody* UAuthV2RefreshTokenAuthRequestBodyLibrary::Make(FOptionalString RefreshToken, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, FOptionalAuthV2ContextInfo Context, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2RefreshTokenAuthRequestBody>(Outer);
	Serializable->RefreshToken = RefreshToken;
	Serializable->CustomerId = CustomerId;
	Serializable->RealmId = RealmId;
	Serializable->Context = Context;
	
	return Serializable;
}

void UAuthV2RefreshTokenAuthRequestBodyLibrary::Break(const UAuthV2RefreshTokenAuthRequestBody* Serializable, FOptionalString& RefreshToken, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId, FOptionalAuthV2ContextInfo& Context)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		RefreshToken = Serializable->RefreshToken;
		CustomerId = Serializable->CustomerId;
		RealmId = Serializable->RealmId;
		Context = Serializable->Context;
	}
		
}

