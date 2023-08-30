
#include "BeamableCore/Public/AutoGen/RefreshTokenAuthRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString URefreshTokenAuthRequestBodyLibrary::RefreshTokenAuthRequestBodyToJsonString(const URefreshTokenAuthRequestBody* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

URefreshTokenAuthRequestBody* URefreshTokenAuthRequestBodyLibrary::Make(FOptionalString RefreshToken, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, UObject* Outer)
{
	auto Serializable = NewObject<URefreshTokenAuthRequestBody>(Outer);
	Serializable->RefreshToken = RefreshToken;
	Serializable->CustomerId = CustomerId;
	Serializable->RealmId = RealmId;
	
	return Serializable;
}

void URefreshTokenAuthRequestBodyLibrary::Break(const URefreshTokenAuthRequestBody* Serializable, FOptionalString& RefreshToken, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId)
{
	RefreshToken = Serializable->RefreshToken;
	CustomerId = Serializable->CustomerId;
	RealmId = Serializable->RealmId;
		
}

