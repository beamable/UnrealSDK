
#include "BeamableCore/Public/AutoGen/CustomerActorNewGameRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCustomerActorNewGameRequestBodyLibrary::CustomerActorNewGameRequestBodyToJsonString(const UCustomerActorNewGameRequestBody* Serializable, const bool Pretty)
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

UCustomerActorNewGameRequestBody* UCustomerActorNewGameRequestBodyLibrary::Make(FString GameName, FOptionalBool bIsHidden, UObject* Outer)
{
	auto Serializable = NewObject<UCustomerActorNewGameRequestBody>(Outer);
	Serializable->GameName = GameName;
	Serializable->bIsHidden = bIsHidden;
	
	return Serializable;
}

void UCustomerActorNewGameRequestBodyLibrary::Break(const UCustomerActorNewGameRequestBody* Serializable, FString& GameName, FOptionalBool& bIsHidden)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		GameName = Serializable->GameName;
		bIsHidden = Serializable->bIsHidden;
	}
		
}

