
#include "BeamableCore/Public/AutoGen/CreateRealmRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCreateRealmRequestBodyLibrary::CreateRealmRequestBodyToJsonString(const UCreateRealmRequestBody* Serializable, const bool Pretty)
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

UCreateRealmRequestBody* UCreateRealmRequestBodyLibrary::Make(FString Name, FOptionalBool bIsHidden, FOptionalBool bSharded, FOptionalString Plan, FOptionalString Parent, UObject* Outer)
{
	auto Serializable = NewObject<UCreateRealmRequestBody>(Outer);
	Serializable->Name = Name;
	Serializable->bIsHidden = bIsHidden;
	Serializable->bSharded = bSharded;
	Serializable->Plan = Plan;
	Serializable->Parent = Parent;
	
	return Serializable;
}

void UCreateRealmRequestBodyLibrary::Break(const UCreateRealmRequestBody* Serializable, FString& Name, FOptionalBool& bIsHidden, FOptionalBool& bSharded, FOptionalString& Plan, FOptionalString& Parent)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		bIsHidden = Serializable->bIsHidden;
		bSharded = Serializable->bSharded;
		Plan = Serializable->Plan;
		Parent = Serializable->Parent;
	}
		
}

