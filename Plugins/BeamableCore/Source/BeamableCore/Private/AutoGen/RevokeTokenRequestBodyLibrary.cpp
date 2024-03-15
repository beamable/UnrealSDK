
#include "BeamableCore/Public/AutoGen/RevokeTokenRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString URevokeTokenRequestBodyLibrary::RevokeTokenRequestBodyToJsonString(const URevokeTokenRequestBody* Serializable, const bool Pretty)
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

URevokeTokenRequestBody* URevokeTokenRequestBodyLibrary::Make(FString Token, UObject* Outer)
{
	auto Serializable = NewObject<URevokeTokenRequestBody>(Outer);
	Serializable->Token = Token;
	
	return Serializable;
}

void URevokeTokenRequestBodyLibrary::Break(const URevokeTokenRequestBody* Serializable, FString& Token)
{
	Token = Serializable->Token;
		
}

