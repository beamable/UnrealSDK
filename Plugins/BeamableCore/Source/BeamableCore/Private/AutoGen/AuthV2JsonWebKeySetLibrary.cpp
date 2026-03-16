
#include "BeamableCore/Public/AutoGen/AuthV2JsonWebKeySetLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2JsonWebKeySetLibrary::AuthV2JsonWebKeySetToJsonString(const UAuthV2JsonWebKeySet* Serializable, const bool Pretty)
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

UAuthV2JsonWebKeySet* UAuthV2JsonWebKeySetLibrary::Make(FOptionalArrayOfAuthV2JsonWebKey Keys, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2JsonWebKeySet>(Outer);
	Serializable->Keys = Keys;
	
	return Serializable;
}

void UAuthV2JsonWebKeySetLibrary::Break(const UAuthV2JsonWebKeySet* Serializable, FOptionalArrayOfAuthV2JsonWebKey& Keys)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Keys = Serializable->Keys;
	}
		
}

