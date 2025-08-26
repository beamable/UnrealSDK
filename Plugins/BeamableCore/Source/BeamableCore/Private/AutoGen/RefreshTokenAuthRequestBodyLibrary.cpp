
#include "BeamableCore/Public/AutoGen/RefreshTokenAuthRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URefreshTokenAuthRequestBodyLibrary::RefreshTokenAuthRequestBodyToJsonString(const URefreshTokenAuthRequestBody* Serializable, const bool Pretty)
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

URefreshTokenAuthRequestBody* URefreshTokenAuthRequestBodyLibrary::Make(FOptionalString RefreshToken, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, FOptionalContextInfo Context, UObject* Outer)
{
	auto Serializable = NewObject<URefreshTokenAuthRequestBody>(Outer);
	Serializable->RefreshToken = RefreshToken;
	Serializable->CustomerId = CustomerId;
	Serializable->RealmId = RealmId;
	Serializable->Context = Context;
	
	return Serializable;
}

void URefreshTokenAuthRequestBodyLibrary::Break(const URefreshTokenAuthRequestBody* Serializable, FOptionalString& RefreshToken, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId, FOptionalContextInfo& Context)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		RefreshToken = Serializable->RefreshToken;
		CustomerId = Serializable->CustomerId;
		RealmId = Serializable->RealmId;
		Context = Serializable->Context;
	}
		
}

