
#include "BeamableCore/Public/AutoGen/ListTokenResponseItemLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UListTokenResponseItemLibrary::ListTokenResponseItemToJsonString(const UListTokenResponseItem* Serializable, const bool Pretty)
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

UListTokenResponseItem* UListTokenResponseItemLibrary::Make(FString Token, FString Platform, FString Device, FString Created, UObject* Outer)
{
	auto Serializable = NewObject<UListTokenResponseItem>(Outer);
	Serializable->Token = Token;
	Serializable->Platform = Platform;
	Serializable->Device = Device;
	Serializable->Created = Created;
	
	return Serializable;
}

void UListTokenResponseItemLibrary::Break(const UListTokenResponseItem* Serializable, FString& Token, FString& Platform, FString& Device, FString& Created)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Token = Serializable->Token;
		Platform = Serializable->Platform;
		Device = Serializable->Device;
		Created = Serializable->Created;
	}
		
}

