
#include "BeamableCore/Public/AutoGen/CreateProjectRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCreateProjectRequestBodyLibrary::CreateProjectRequestBodyToJsonString(const UCreateProjectRequestBody* Serializable, const bool Pretty)
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

UCreateProjectRequestBody* UCreateProjectRequestBodyLibrary::Make(FString Name, FOptionalBool bSharded, FOptionalString Plan, FOptionalString Parent, UObject* Outer)
{
	auto Serializable = NewObject<UCreateProjectRequestBody>(Outer);
	Serializable->Name = Name;
	Serializable->bSharded = bSharded;
	Serializable->Plan = Plan;
	Serializable->Parent = Parent;
	
	return Serializable;
}

void UCreateProjectRequestBodyLibrary::Break(const UCreateProjectRequestBody* Serializable, FString& Name, FOptionalBool& bSharded, FOptionalString& Plan, FOptionalString& Parent)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		bSharded = Serializable->bSharded;
		Plan = Serializable->Plan;
		Parent = Serializable->Parent;
	}
		
}

